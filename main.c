#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int ReadTraceFile(char * FileName, int pageOffset, int quantum, int startByte);
unsigned int convert32bitCharToInt(unsigned char buffer[], int pageOffset);



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
    char *policy = argv[6];

    printf("\n***********CMPUT379***********\n");
    printf("pgsize: %hu\n", pgsize);
    printf("tlbentries: %u\n", tlbentries);
    printf("mode: %s\n", mode);
    printf("quantum: %d\n", quantum);
    printf("physpages: %d\n", physpages);
    printf("policy: %s\n", policy);
    
	int fileLineToRead[argc - 7];
	int fileEOFReached[argc - 7];
	int i, j;

	//We're always dealing with a 32bit mem-ref.
	//Get the page offset. represents the number of bits used in the offset.
	int pageOffset = (log(pgsize) / log(2));
	//printf("offset: %d\n", pageOffset);

	//Create an array that will hold the read in pages. 
	unsigned int pageTable[physpages];
	
	//Set all fileNotEmpty to true/1
	for(i = 0; i < argc - 7; i++) {
		fileLineToRead[i] = 0;
		fileEOFReached[i] = 1;
	}
	i = 7;
	while(TraceEOFCheck(fileEOFReached, argc - 7) == 1){
		printf("Reading File: %s\n",argv[i]);
		fileEOFReached[i - 7] = ReadTraceFile(argv[i], pageOffset, quantum, fileLineToRead[i - 7]);
		//printf("fileEOFReached[%d]: %d\n",i, fileEOFReached[i]);
		fileLineToRead[i - 7] = fileLineToRead[i-7] + quantum;
		i += 1;
		if(i >= argc)
			i = 7;
	}

	return 0;
}

int TraceEOFCheck (int EOFtracker[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		//printf("EOF%d: %d\n", i , EOFtracker[i]);
		if (EOFtracker[i] == 1) {
			//printf("EOF Check returning 1\n");
			return 1;
		}
	}
	//printf("EOF Check returning 0\n");
	return 0;
}

unsigned int convert32bitCharToInt(unsigned char buffer[], int pageOffset){
	unsigned int val = 0;	
	val = (unsigned int)buffer[0] << 24 | (unsigned int)buffer[1] << 16 | (unsigned int)buffer[2] << 8 | (unsigned int)buffer[3];
	val = val >> pageOffset;
	return val;
}

int ReadTraceFile(char * FileName, int pageOffset, int quantum, int startByte) {
	int i, j;
	int bytesToRead = 4; //4bytes * 8bits = 32 bits
	FILE *fp;	
	fp = fopen(FileName, "rb");
	unsigned char buffer[bytesToRead];
	unsigned int pageNumber = 0;
	for(j = 0; j < quantum + startByte; j++) {
		if (fread(buffer,bytesToRead,1,fp) == 1) {
			if(j >= startByte) {
				printf("%d: ", j);
				for(i = 0; i < bytesToRead; i++) {
					printf("%x ", buffer[i]);
				}
				pageNumber = convert32bitCharToInt(buffer, pageOffset);
				printf("page#: %d\n", pageNumber);
			}
		}
		else
		{
			printf("End of file reached.\n");
			return 0;
		}
		
	}
	fclose(fp);
	return 1;
}
