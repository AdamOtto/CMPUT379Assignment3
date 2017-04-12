#include <stdio.h>
#include <stdlib.h>

/* How to initialize:
 *
 * struct FIFO_Queue q;
 * int size = 10;
 * q.size = size;
 * *q.element_count = 0;
 * q.array = (int*) malloc(sizeof(int) * size);
 */

struct FIFO_Queue {
    int size;
    int *array;
    int *element_count;
};

int FIFO_TBL_hit(struct FIFO_Queue q, int newOb) {
    int i;
    for (i = 0; i < q.size; i++) {
        if (q.array[i] == newOb)
            return 1;
    }
    return 0; 
}

int FIFO_Enqueue(struct FIFO_Queue q, int newOb) {
    int i;
    int DiscardedValue;

    for (i = q.size - 1; i >= 1; i--) {
        q.array[i] = q.array[i-1];
    }
    DiscardedValue = q.array[0];
    q.array[0] = newOb;
    *q.element_count = *q.element_count + 1;
    return DiscardedValue;
}
