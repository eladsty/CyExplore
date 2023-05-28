#ifndef __ATOIITOA_H_CR4__ 
#define __ATOIITOA_H_CR4__ 


#define REPCON_ITOA(x) (x < 10) ? (x + 48) : (x + 55)
#define REPCON_ATOI(x) (x > 65) ? (x - 55) : (x - 48)
#define IS_LITTLE_ENDIAN() ((char*)'1' - 48)

char *ItoA(int n, char *buffer, int radix);
int Atoi(const char *nptr);
char *ItoA36(int n, char *buffer, int radix);
int Atoi36(const char *nptr, int radix);
int TestFunc();
void InTwoOutOfThree(char *arr1,char *arr2, char *arr3);
void IsLittleEndian(void);

#endif /* __ATOIITOA_H_CR4__ */
