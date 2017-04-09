
/* The following machine parameters are being used:
   
   Number of bits in an address: 32
   Page size: 4KB
   Size of Physical Memory: Configurable - see documentation
   Size of TLB: Configurable - see documentation

   Page Table Type:  2 level page table
   Size of first level page table: 1024 entries
   Size of first level Page Table Entry:  32 bits
   Size of 2nd Level Page Table: 1024 entries
   Size of 2nd Level Page Table Entry: 32 bits

   Three bitmaps are used to keep track of the 
   "present", M, and R bits of each physical
   page frame:
    - A bitmap of "present" bits, where the i'th
      bit is 1 if the i'th page frame is occupied
      and 0 if the page frame is free.
    - A bitmap of M bits, where the i'th bit is
      1 if the i'th page frame has been written to
      by a STORE instruction.
    - A bitmap of R bits, where the i'th bit is
      1 if the i'th page frame has been referenced
      (by a LOAD or STORE instruction).
*/


void mmu_initialize();

// This sets the bit in the R bit bitmap corresponding
// to the specified page frame to the specified value (0 or 1)
void mmu_modify_rbit_bitmap(PAGEFRAME_NUMBER pframe, int val);

// This returns the value (0 or 1) of the bit in
// the R bit bitmap corresponding to the specified
// page frame.
int mmu_get_rbit_bitmap_value(PAGEFRAME_NUMBER pframe);

// This is used to report the number of TLB misses.
// The count is maintained by the MMU.
extern unsigned int tlb_miss_count;

// This clears all the bits in the R bit bitmap
// and the TLB. It will be invoked upon every clock
// interrupt.
void mmu_clear_rbits();

// This sets the bit in the M bit bitmap corresponding
// to the specified page frame to the specified value (0 or 1)
void mmu_modify_mbit_bitmap(PAGEFRAME_NUMBER pframe, int val);

// This returns the value (0 or 1) of the bit in
// the M bit bitmap corresponding to the specified
// page frame.
int mmu_get_mbit_bitmap_value(PAGEFRAME_NUMBER pframe);

// This is the main MMU function, mapping the
// specified virtual address to a physical address. 
// It also is passed the operation (LOAD or STORE),
// since the operation will affect the status of the
// M bit of the accessed page frame.
ADDRESS mmu_translate(ADDRESS vaddress, OPERATION op);

//See function below
#define NO_FREE_PAGEFRAME ~0x0

// This returns a free page frame, if 
// there is one. It records in the pageframe
// bitmap that the returned page frame is
// no longer available. If there is no
// no free pageframe, NO_FREE_PAGEFRAME 
// is returned.
PAGEFRAME_NUMBER mmu_get_free_page_frame();
