#include "tlb.h"

tlb_entry *tlb;

void tlb_init(unsigned char tlb_size) {

    tlb = (tlb_entry *) malloc(num_tlb_entries * sizeof(tlb_entry));

}

void tlb_flush(int tlb_size) {

    int i;
    for (i = 0; i < tlb_size; i++) {
        tlb[i].valid = 0;
    }
}

void tlb_clear(int tlb_size, int page_number) {

    int i;
    for (i = 0; i < tlb_size; i++) {
        if (tlb[i].page_number == page_number) {
            tlb[i].valid = 0;
        }
    }
}

void tlb_free()
    free(tlb);
}
            
    


