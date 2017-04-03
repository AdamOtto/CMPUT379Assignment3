#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadTraceFile(char * FileName, int pageSize, int tblEntry, int quantum);
int checkIfAllFilesAreRead(int fileFlags[], int size);

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
    
    int fileNotEmpty[argc - 7];
    int fileLineToRead[argc - 7];
    int i;
/*
    //Set all fileNotEmpty to true/1
    for(i = 0; i < argc - 7; i++) {
         fileNotEmpty[i] = 1;
         fileLineToRead[i] = 0;
    }

    while(checkIfAllFilesAreRead(fileNotEmpty,argc - 7)){
	    for(i = 7; i < argc; i++) {
		if(fileNotEmpty[i - 7]){
		    fileNotEmpty[i - 7] = ReadTraceFile(argv[i], quantum, fileLineToRead[i-7]);
                    fileLineToRead[i - 7] = fileLineToRead[i-7] + quantum;
                }
	    }
    }
*/	
	ReadTraceFile(argv[0], pgsize, tlbentries, quantum);

    return 0;

}

int checkIfAllFilesAreRead(int fileFlags[], int size)
{
	int i;
	for(i = 0; i < size; i++) {
		if(fileFlags[i]) {
			return 1;
		}
	}
	return 0;
}

int ReadTraceFile(char * FileName, int pageSize, int tblEntry, int quantum) {
	int i, j;
	int bytesToRead = (pageSize + tblEntry) / 8;
	FILE *fp;	
	fp = fopen(FileName, "rb");
	unsigned char buffer[bytesToRead];
	
	for(j = 0; j< quantum; j++) {
		
		if (fread(buffer,bytesToRead,1,fp) == 1) {
			for(i = 0; i < bytesToRead; i++)
				printf("%x ", buffer[i]);
			printf("\n");
		}
	}
	
	/*
	for(i = 0; i < quantum + startLine; i++) {
		if (fscanf(fp, "%s", line) != EOF)
		{
			if(i >= startLine) {
				//This is where we should process the read in lines.
				printf("%s\n",line);
			}
		}
		else
		{
			return 0;
		}
	}
	*/
	fclose(fp);
	return 1;
}










