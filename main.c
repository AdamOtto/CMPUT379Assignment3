#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIFO_Queue.h"
#include "LRU_Stack.h"
#include "PageTable.c"

int ReadTraceFile(FILE * fp, int pageOffset, int quantum, int globalIndex);
unsigned int convert32bitCharToInt(unsigned char buffer[], int pageOffset);
void FIFO_Process(int pageNumber, int globalIndex);
void LRU_Process(int pageNumber, int globalIndex);

//FIFO_q and LRU_q represent the physical memory.
struct FIFO_Queue FIFO_q;
struct LRU_Stack LRU_q;

//TLB
struct LRU_Stack TLB;

// PageTable
PageTable **root;

// The policy, considered read only after being set.
char * policy;

// These contain the stats that are collected for each trace file.
int * TLBhits;
int * PageFault;
int * PHYSpageout;
float * PageSizeAvg;
int * PageSizeReadCount;

int main(int argc, char *argv[]) {

    if (argc < 8) {
        printf("Incorrect number of arguments supplied.\n");
        exit(1);
    }

    unsigned short pgsize = (unsigned short) strtoul(argv[1], NULL, 0);
    unsigned char tlbentries = (unsigned char) strtoul(argv[2], NULL, 0);
    char *mode = argv[3];
    unsigned int quantum = (unsigned int) strtoul(argv[4], NULL, 0);
    unsigned int physpages = (unsigned int) strtoul(argv[5], NULL, 0);
    policy = argv[6];

    int fileLineToRead[argc-7];
    int fileEOFReached[argc-7];
    int i, j;

    // Allocate space for the global stats.
    TLBhits = (int *) malloc(sizeof(int) * argc-7);
    PageFault = (int *) malloc(sizeof(int) * argc-7);
    PHYSpageout = (int *) malloc(sizeof(int) * argc-7);
    PageSizeAvg = (float *) malloc(sizeof(float) * argc-7);
    PageSizeReadCount = (int *) malloc(sizeof(int) * argc-7);

    // We're always dealing with a 32bit mem-ref.
    // Get the page offset. represents the number of bits used in the offset.
    int pageOffset = (log(pgsize) / log(2));

    // Create a pointer to each file given and opens them for future reading.
    FILE **traceFiles;
    traceFiles = (FILE **)malloc(sizeof(FILE) * argc - 7);
    for (i = 7; i < argc; i++) {
        traceFiles[i - 7] = fopen(argv[i], "rb");
    }

    root = (PageTable **) malloc(sizeof(struct PageTable) * argc - 7);
    for (i = 7; i < argc; i++) {
        root[i] = NULL;
    }

    // Allocates memory for the physical pages depending on the policy.
    if (*policy == 'f') {
        FIFO_q.size = physpages;
        FIFO_q.element_count = (int*)malloc(sizeof(int));
        *FIFO_q.element_count = 0;
        FIFO_q.array = (int*)malloc(sizeof(int) * physpages);
    }
    else if (*policy == 'l') {
        LRU_q.size = physpages;
        LRU_q.element_count = (int*)malloc(sizeof(int));
        *LRU_q.element_count = 0;
        LRU_q.array = (int*)malloc(sizeof(int) * physpages);
    }

    // Creates space for the TLB.
    TLB.size = tlbentries;
    TLB.element_count = (int*)malloc(sizeof(int));
    *TLB.element_count = 0;
    TLB.array = (int*) malloc(sizeof(int) * tlbentries);
    // Sets all of TLB to a negative number in order to prevent potentially wrong TLB hits.
    for(i = 0; i < tlbentries; i++)
        TLB.array[i] = -1;

    // Set all fileNotEmpty to true
    for (i = 0; i < argc - 7; i++) {
        fileLineToRead[i] = 0;
        fileEOFReached[i] = 1;
    }
    i = 0;
    while (TraceEOFCheck(fileEOFReached, argc - 7) == 1){
        fileEOFReached[i] = ReadTraceFile(traceFiles[i], pageOffset, quantum, i);
        fileLineToRead[i] = fileLineToRead[i] + quantum;
        i += 1;
        if (i >= argc - 7)
            i = 0;
        // If process specific, clear TLB.
        if (*mode == 'p'){
            int i_2;
            for (i_2 = 0; i_2 < tlbentries; i_2++)
                TLB.array[i_2] = -1;
        }
    }
    for (i = 0; i < argc - 7; i++) {
        printf("%d %d %d %f\n", TLBhits[i], PageFault[i], PHYSpageout[i], (float)(PageSizeAvg[i] / PageSizeReadCount[i]));
        fclose(traceFiles[i]);
    }
    return 0;
}

int TraceEOFCheck (int EOFtracker[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (EOFtracker[i] == 1) {
            return 1;
        }
    }
    return 0;
}

unsigned int convert32bitCharToInt(unsigned char buffer[], int pageOffset){
    unsigned int val = 0;	
    val = (unsigned int) buffer[0] << 24 | (unsigned int) buffer[1] << 16 |
          (unsigned int) buffer[2] << 8 | (unsigned int) buffer[3];
    val = val >> pageOffset;
    return val;
}

int ReadTraceFile(FILE * fp, int pageOffset, int quantum, int globalIndex) {
    int i, j, hit_index;
    int bytesToRead = 4; // 4bytes * 8bits = 32 bits
    unsigned char buffer[bytesToRead];
    unsigned int pageNumber = 0;
    for (j = 0; j < quantum; j++) {
        if (fread(buffer,bytesToRead,1,fp) == 1) {
            pageNumber = convert32bitCharToInt(buffer, pageOffset);
            // Process for the LRU_TLB
            hit_index = LRU_TBL_hit(TLB, pageNumber);

            // If hit, then we are done.
            if (hit_index != -1) {
                LRU_add(TLB, pageNumber, hit_index);
                TLBhits[globalIndex] = TLBhits[globalIndex] + 1;
            }
            // If miss, check pageTable here.
            else {
                // If pageTable hit, we're done.
                int b = insert(&root[globalIndex], pageNumber, NULL);
                if (b) { 
                    TLBhits[globalIndex] = TLBhits[globalIndex] + 1;
                    // Add the missed pageNumber into TLB.
                    LRU_add(TLB, pageNumber, hit_index);
                } else {
                    PageFault[globalIndex] = PageFault[globalIndex] + 1;	
                    // If pageTable miss, then add into memory.
                    if (*policy == 'f') {
                        FIFO_Process(pageNumber, globalIndex);
                    }
                    else if (*policy == 'l') {
                        LRU_Process(pageNumber, globalIndex);
                    }
                }
            }
            // Take the new PageSize average.
            PageSizeReadCount[globalIndex] = PageSizeReadCount[globalIndex] + 1;
            PageSizeAvg[globalIndex] = (float)( PageSizeAvg[globalIndex] + sizeOf(root[globalIndex], 0) );
        } else {
            return 0;
        }		 
    }
    return 1;
}

void FIFO_Process(int pageNumber, int globalIndex) {
    if (FIFO_TBL_hit(FIFO_q, pageNumber) == 0) {
        FIFO_Enqueue(FIFO_q, pageNumber);
        if (*FIFO_q.element_count > FIFO_q.size)
            PHYSpageout[globalIndex] = PHYSpageout[globalIndex] + 1;
    }
}

void LRU_Process(int pageNumber, int globalIndex) {
    int pageOut = 1;
    int hit_index = LRU_TBL_hit(LRU_q, pageNumber);
    pageOut = LRU_add(LRU_q, pageNumber, hit_index);
    if (pageOut == 1)
        PHYSpageout[globalIndex] = PHYSpageout[globalIndex] + 1;
}
