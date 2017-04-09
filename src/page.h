
extern BOOL page_fault;

void pt_intialize_page_table();

// Using the page table, this looks up the page frame 
// corresponding to the specified virtual page.
PAGEFRAME_NUMBER pt_get_pageframe(VPAGE_NUMBER vpage);

// This inserts into the page table the mapping of the 
// the specified virtual page to the specified page frame.
void pt_update_pagetable(VPAGE_NUMBER vpage, PAGEFRAME_NUMBER pframe);


// This clears a page table entry by clearing its present bit.
// It is called by the OS (in kernel.c) when a page is evicted
// from a page frame.
void pt_clear_page_table_entry(VPAGE_NUMBER vpage);
