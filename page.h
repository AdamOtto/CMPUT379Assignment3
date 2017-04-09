typedef struct {
    int PageNumber;       // Page #
    int FrameNumber;      // Frame #
    int Valid;            // Valid or invalid bit
    } page_table_entry;

typedef page_table_entry *page_table;
