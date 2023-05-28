#include "structs.h" /* function declaration */

/* string input will only be allowed using CreateString */
int main()
{
	int a = 7, b = 15000, n[5] = {1, 7, 10, 19, -225}, i, su, sx, sc;
	float c = 2.3;
	void *d, *e;
	int max2_test = MAX2(a, b);
	int max3_test = MAX3(a, n[3], n[4]);
	printf("max2 is %d, max 3 is %d\n", max2_test, max3_test);
	printf("size of is %ld\n", SIZEOF_VAR(a));
	printf("size of type is %ld\n", SIZEOF_TYPE(unsigned char));
	
	
	union numbers
	{
		int i;
		float f;
		double d;
	} u;
	
	struct X
	{
		int i;
		char c;
		double d;
		short s;
	} x;
	printf("size of type is %ld\n", SIZEOF_TYPE(union numbers));
	struct card
	{
		unsigned int suit : 2;
		unsigned int face : 4;
	} ca;

	
	su = sizeof(u);
	sx = sizeof(x);
	sc = sizeof(ca);
	printf("size of union: %d, struct x: %d, card: %d\n", su, sx, sc);
	
	
	
	d = CreateString("Shani", 6);
	e = CreateString("1254756", 8);
	
	struct element arr[5] = {
		{(void*)&a, AddInt, PrintInt, CleaUpInt},
		{(void*)&b, AddInt, PrintInt, CleaUpInt},
		{(void*)&c, AddFlt, PrintFlt, CleaUpFlt},
		{(void*)d, AddStr, PrintStr, CleaUpStr},
		{(void*)e, AddStr, PrintStr, CleaUpStr}
		};
	
	for (i = 0; i < 5; i++)
		{
			arr[i].print(arr[i].pointer);
			arr[i].add(&arr[i].pointer, n[i]);
			arr[i].print(arr[i].pointer);
			arr[i].clean(arr[i].pointer);	
		}
		
	return 0;
}

