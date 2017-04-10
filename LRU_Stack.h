struct LRU_Stack {
	int size;
	int * array;
	int * element_count;
	};
/*
How to initialize:
	struct LRU_Stack q;
	int size = 10;
	q.size = size;
	*q.element_count = 0;
	q.array = (int*)malloc(sizeof(int) * size);

	if q is global, you'll have to allocate memory to q.element_count as well.
*/


int TBL_hit(struct LRU_Stack q, int newOb) {
	int i;
	for (i = 0; i < q.size; i++)
		if (q.array[i] == newOb)
			return i;
	return -1; 
}

/*
If LRU_add returns 0, then a pageout didn't occur.
If LRU_add returns 1, then a pageout occured.*/
int LRU_add(struct LRU_Stack q, int newOb) {
	int i, j;
	j = TBL_hit(q, newOb);
	if( j != -1)
	{
		printf("%d is already in q.\n", newOb);
		for (i = j; i < q.size - 1; i++)
		{
			q.array[i] = q.array[i + 1];			
		}
		q.array[*q.element_count - 1] = newOb;
		return 0;
	}
	else
	{
		if(*q.element_count >= q.size)
		{
			for (i = 0; i < q.size - 1; i++)
			{
				q.array[i] = q.array[i + 1];			
			}
			q.array[*q.element_count - 1] = newOb;
		
			if(*q.element_count + 1 <= q.size){
				*q.element_count = *q.element_count + 1;
			}
			return 1;
		}
		else {
			q.array[*q.element_count] = newOb;
		
			if(*q.element_count + 1 <= q.size){
				*q.element_count = *q.element_count + 1;
			}
			return 0;
		}
	}
}



