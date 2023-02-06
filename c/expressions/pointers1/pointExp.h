int SwapValues(int *a, int *b)
{
	int temp;
	assert (a != NULL);
 	assert (b != NULL);
	temp = *a;
	*a = *b;
	*b = temp;

	return 1;
}


int *CopyArr(int *source, int N)
{
	int i;
	int *ptr_cpy = NULL;
	assert(source != NULL);
	ptr_cpy = malloc(N*sizeof(int));

	for(i=0; i<N ;i++)
		{
			*ptr_cpy = *source;
			ptr_cpy++;
			source++;
		}
	
	return ptr_cpy;
}

int Printer()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	int **ptr3;
	
	if(ptr)
	{
		int **ptr3 = &ptr;
	}
	
	free(ptr2);
	
	printf("static int: %p \n",(void *)&s_i);
	printf("int: %p \n",(void *)&i);
	printf("static int: %p \n", (void *)&ptr);
	printf("static int: %p \n", (void *)&ptr2);
	printf("static int: %p \n", (void *)&ptr3);
	
	return 0;
}

void SwapSizet(size_t *size1 ,size_t *size2)
{
	size_t temp=0;
	assert(size1 != NULL);
	assert(size2 != NULL);
	
	temp = *size1;
	*size1 = *size2;
	*size2 = temp;
	
}

void SwapSizetptr(size_t **size1, size_t **size2)
{
	size_t *temp;
	assert(size1 != NULL);
	assert(size2 != NULL);
	
	temp = *size1;
	*size1 = *size2;
	*size2 = temp;
}



 
 

