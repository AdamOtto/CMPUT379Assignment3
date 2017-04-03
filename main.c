#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadTraceFile(char * FileName, int pageSize, int tblEntry, int quantum, int startByte);

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
    int i, j;

    //Set all fileNotEmpty to true/1
    for(i = 0; i < argc - 7; i++) {
         fileLineToRead[i] = 0;
    }
    i = 7;
    j = 0;
    while(j < physpages){
	printf("Pages Read: %d\n",j);
	ReadTraceFile(argv[i], pgsize, tlbentries, quantum, fileLineToRead[i - 7]);
	fileLineToRead[i - 7] = fileLineToRead[i-7] + quantum;
	j += quantum;
	i += 1;
	if(i >= argc)
		i = 7;
    }

    return 0;

}

int ReadTraceFile(char * FileName, int pageSize, int tblEntry, int quantum, int startByte) {
	int i, j;
	int bytesToRead = (pageSize + tblEntry) / 8;
	FILE *fp;	
	fp = fopen(FileName, "rb");
	unsigned char buffer[bytesToRead];
	for(j = 0; j < quantum + startByte; j++) {
		if (fread(buffer,bytesToRead,1,fp) == 1) {
			
			if(j >= startByte) {
				printf("%d: ", j);
				for(i = 0; i < bytesToRead; i++) {
					printf("%x ", buffer[i]);
				}
				printf("\n");
			}
		}
		else
			return 0;
		
	}
	fclose(fp);
	return 1;
}
