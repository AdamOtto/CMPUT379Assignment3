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


int LRU_TBL_hit(struct LRU_Stack q, int newOb) {
	int i;
	for (i = 0; i < q.size; i++)
		if (q.array[i] == newOb)
			return i;
	return -1; 
}

/*
If LRU_add returns 0, then a pageout didn't occur.
If LRU_add returns 1, then a pageout occured.

If the new Object isn't in q, then the passed in TLB_hit_index should be set to -1.
*/
int LRU_add(struct LRU_Stack q, int newOb, int TLB_hit_index) {
	int i;
	//j = TBL_hit(q, newOb);
	if( TLB_hit_index != -1)
	{
		for (i = TLB_hit_index; i < q.size - 1; i++)
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



