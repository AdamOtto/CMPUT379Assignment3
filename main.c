#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("trace: ");


    return 0;

}
