#include <stdio.h>

#define MAX3(a,b,c) ((a > b) ? a : b) > c ? ((a > b) ? a : b) : c
#define TO_LOWER(a) (a > 64) && (a < 91) ? (a + 32) : a
#define OFFSET(s, f) (size_t)&f - (size_t)&s
int main()
{
	int a = 15, b = 8, c = 1;
	char m = 'W';
	struct su {
		int a;
		char c;
		float f;
	} s;
	
	printf("%d\n", OFFSET(s, s.f));
	printf("%d\n", TO_LOWER(m));
	printf("%d\n", MAX3(a, b, c));
	return 0;
}

