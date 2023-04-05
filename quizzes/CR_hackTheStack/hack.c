#include <stdio.h>
void func2(void *arg)
{
    long f2;
    printf("Enter func2\n");
    /* area 2 */
          
*(&f2 + 3) = *(long *)((long *)arg + 3	) ;  
	
*(long *)((long *)arg + 3 ) = *(long *)((long *)arg + 7 ) ;  

 
printf("Exit func2\n");
}

void func1()
{
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");

} 

int main()
{
    const long x = 1;
    long y = 5;
   
 /* area 1 */
  
   *(long *)&x = 1337;
  *(&y + 1) = 1337;

 
     printf("x = %lu\n", x);
    func1();

    printf("Exit main\n");

    return 0;
}
