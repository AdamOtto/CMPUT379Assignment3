typedef struct {
    int PageNumber;
    int ProcessID;
    int FrameNumber;
    int Valid;
    } TLB_entry;

typedef TLB_entry* TLB_pointer;
