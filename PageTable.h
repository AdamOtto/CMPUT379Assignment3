//-----------------------------------------------------------------------------
typedef struct {
    int PageNumber;
    int ProcessID;
    int FrameNumber;
    int Valid;
    } page_table_entry;

typedef page_table_entry* page_table_pointer;
//-----------------------------------------------------------------------------