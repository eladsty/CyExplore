#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void func2(void *arg) {
    long f2;
	/* q2 - change x to 1337 without using it */
	/*char *ptr = (char *)arg + 32;
	*(long *)ptr = (long)1337;*/
    printf("Enter func2\n");
    /* q3 - lvalue is dereference of the return adress from func2 to func1, 
		I put in 16 bytes after that adress, bypassing the printf call */
	*(long *)(&f2 + 3) = *(long *)(&f2 + 3) + 16;

    printf("Exit func2\n");
	
}
void func1() {
    long f1;

    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}
 
int main() {
    const long x=1;
    long y=5;
 
    /* AREA1 */
	/* q1 - change x to 1337 */
	/*long *px = (long *)&x;
	*px = 1337;*/


    printf("x=%lu\n",x);
    func1();
 
    printf("Exit main\n");
    return 0;
}