struct Page_Table {
    int size;
    int *array;
};

int pageExists(struct Page_Table pt, int pageNumer) {
    int i;
    for (i = 0; i < q.size; i++) {
        if (pt.array[i] == pageNumber) {
            return i + 1;
        }
    }
    return 0;
}

int addPage(struct Page_Table pt, int pageNumber) {
    int i = pageExists(pt, pageNumber);
    if (i) {
        return 0;
    } else {
        int j = pt.size;
        pt.array[j] = pageNumber;
        pt.size++;
    }
}
