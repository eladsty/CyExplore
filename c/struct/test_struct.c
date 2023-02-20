

#include "struct.h"

int main()
{
	check check_arr[3];
		union car car1;
		struct X x;
	int num = 8;
	float num_float = 9.6;
	char *str;
	str = (char *)malloc(sizeof(char) * 8);
	strcpy(str, "testing");

	check_arr[0].p = (void *)&num;
	check_arr[1].p = (void *)&num_float;
	check_arr[2].p = (void *)str;
	
	check_arr[0].add = &AddInt;
	check_arr[1].add = &AddFloat;
	check_arr[2].add = &AddStr;
	
	check_arr[0].print = &PrintInt;
	check_arr[1].print = &PrintFloat;
	check_arr[2].print = &PrintStr;
	
	check_arr[2].cleanup = &CleanStr;
	
	
	check_arr[0].print(check_arr[0].p);
	check_arr[1].print(check_arr[1].p);
	check_arr[2].print(check_arr[2].p);
	
	check_arr[0].add(15, &check_arr[0].p);
	check_arr[1].add(25, &check_arr[1].p);
	check_arr[2].add(26, &check_arr[2].p);
	
	check_arr[0].print(check_arr[0].p);
	check_arr[1].print(check_arr[1].p);
	check_arr[2].print(check_arr[2].p);
	
	check_arr[2].cleanup(check_arr[2].p);

    printf("%ld\n",SIZEOF_VAR(num));
    printf("%ld\n", SIZEOF_TYPE(int));
 
 	 
 
 
printf("size of car is %ld\n", sizeof(car1));
printf("size ofstruct %ld\n", sizeof(x));
	return 0;
}



