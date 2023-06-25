#include <stdio.h>

void func(long a, long b) {

/* below the address of a, the is a pointer for the return address, we change it's value so it will point back to the main function after the num = 4 line */
 *(&a-1) += 10;
  return;
  // Insert lines here
 
  printf("%ld\n", b);
  printf("%ld\n", a);
}

int main() {
  int num = 3;
  func(3, 1);
  num = 4;
  printf("num is now %d\n", num);

  return 0;
}
