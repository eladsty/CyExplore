#include <stdio.h>

#include "vector.h"

int main()
{
	int arr[] = {5,33,61,833,1512,12,99,3};
	double double_arr[] = {1.15 ,33.8 ,61.76 ,833 ,1512.87 ,12.2 ,99.77, 3.552};
	int i = 0;
	vector_t *int_vector = VectorCreate(8,4);
	vector_t *double_vector = VectorCreate(8,8);
	for(i = 0; i<8; ++i)
	{
	VectorPush(int_vector ,&arr[i]);
 	printf("int element at index %d is: %d\n",i ,*((int *)VectorAcessIndex(int_vector,i)));
 	
 	VectorPush(double_vector ,&double_arr[i]);
 	printf("double element at index %d is: %f\n\n",i ,*((double *)VectorAcessIndex(double_vector, i)));
 	
 	printf("number of elements: %ld\n", VectorSize(int_vector));
 	printf("number of elements: %ld\n", VectorSize(double_vector));
	}
	
	for(i=0; i<5; i++)
	{
		printf("int_vector size before pop is: %ld\n", VectorSize(int_vector));
		VectorPop(int_vector);

		printf("double_vector size before pop is: %ld\n", VectorSize(double_vector));
		VectorPop(double_vector);
	}
	  
	printf("VectorAccess (int) at index 1 should be 33: %d\n", *((int *)VectorAcessIndex(int_vector,1)));
	printf("VectorAccess (double) index 1 should be 33.8 : %f\n", *((double *)VectorAcessIndex(double_vector,1)));
	
	
	VectorDestroy(int_vector);
	VectorDestroy(double_vector);
	return 0;
}
