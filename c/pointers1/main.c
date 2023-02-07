#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pointExp.h"

int main()
{
	size_t a = 1;
	size_t b = 2;
	size_t *a_ptr = &a;
	size_t *b_ptr = &b;
	SwapSizetptr(&a_ptr, &b_ptr);
	assert(a_ptr == &b);
 	assert(b_ptr == &a);
	
	return 0;
}




 
