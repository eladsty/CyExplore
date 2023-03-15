
#include "memory_mapping.h"

int i = 1;
const int c_i = 2;
static int s_i = 3;
static const int c_s_i = 4;

static void StaticFunc(int x)
{
	const int c_loc = 3;
	static const int c_s_loc = 4;
	x += 2;
	i = x * 3;
	
	(void)c_loc;
	(void)c_s_loc;
	
	printf("	static x = %d, ", x);
}

extern void ExternFunc(int x)
{
	int *heap = NULL;
	int loc = 3;
	static int s_loc = 4;
	char *s_l = "String literal";
	char str[] = "String arr";
	const char c_str[] = "Const String arr";
	x += 2;
	printf("String literal");
	
	heap = (int *)malloc(sizeof(int) * 10);
	if(heap == NULL)
	{
		printf("HEAP NOT ALLOC'D\n\n");
		exit(2);
	}
	free(heap);
	heap = NULL;
		
	(void)loc;
	(void)s_loc;
	(void)s_l;
	(void)str;
	(void)c_str;
	(void)s_i;
	(void)c_s_i;
	
	StaticFunc(x);
	printf("extern x = %d\n", x);
	
}

