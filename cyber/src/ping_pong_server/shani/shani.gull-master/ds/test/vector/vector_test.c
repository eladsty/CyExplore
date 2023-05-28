#include <string.h> /* strlen, strcpy */
#include "/home/shani/shani.gull/ds/include/vector/vector.h"

int main(void)
{
	char *first[] = {"vectors are the worst", "valgrind is giberish", 
						"cr4 rules", "this is pointless", "I should be fine"};
	char *temp[3];
	int i = 0;
	int n[] = {124}, m[] = {-3};
	const size_t elem_amount = 3, elem_size = strlen(first[1]) + 1;
	size_t index = 10, index2 = 11;

	/* create me some */
	vector_t *vector;
	vector = VectorCreate(elem_amount, elem_size);
	
	/* put some elements in allocated array and printing them from the vector*/
	
	printf("--------\n");
	/* push more elements and print them from vector */
	for ( i = 0; i < 5; ++i)
	{
		VectorPushBack(vector, first[i]);
		printf("%s\n", (char*)VectorAccessIndex(vector, i));
	}
	printf("--------\n");
	/* size of vector */
	printf("size of vector: %ld\n", VectorSize(vector));
	/* resize */
	VectorResize(vector, 10);
	printf("size of vector: %ld\n", VectorSize(vector));
	printf("--------\n");
	/* disgard of element */
	for (i = 0; i < 5; ++i)
	{
		VectorPopBack(vector);
		printf("size of vector: %ld\n", VectorSize(vector));
		printf("%s\n", (char*)VectorAccessIndex(vector, i));
	}
		

	
	/* free allocated */
	VectorDestroy(vector);
	return 0;
}

