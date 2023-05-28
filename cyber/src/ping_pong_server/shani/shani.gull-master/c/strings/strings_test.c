#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "strings.h" 
#include "strings.c"



int main()
{
	const char *test_array[] = {"fdAsABeABCDfsef", "ABBA", "abCd", "moshe", "g"}
		, *test_array2[] = {"ABCD", "ABBA", "IamAbadProg", "moshe", "g"};
	char c[] = {'C', 'A', 'd', 'G', 'g'}, *multy[] = {"NAAAAN","ABCD", "ABBDBBA", 
		"", "AAbbccDDff"}, empty_ptr[100];
	size_t n[] = {2, 11, 7, 4, 60};
	int i = 0;
	char *ptr1, *ptr2;
	char *str = (char*)calloc(100, 1);
	for ( ; i < 4; ++i)
	{
		/* palindrome */
		if (IsPalindrome(multy[i]))
		{
			printf("success\n");
		}
		
		/*testing StrCmp return int*/
		if (StrCmp(test_array[i], test_array2[i]) != strcmp(test_array[i], 
		test_array2[i]))
		{
			printf("1false\n");
		}
		
		/*testing StrLen return size_t*/
		if (StrLen(test_array[i]) != strlen(test_array[i]))
		{
			printf("2false\n");
		}
		
		/*testing StrCaseCmp return int*/
		if (StrCaseCmp(test_array[i], test_array2[i]) != 
		strcasecmp(test_array[i], test_array2[i]))
		{
			printf("3false\n");
		}
	
		/*testing StrnCmp return int*/
		if (StrnCmp(test_array[i], test_array2[i], n[i]) != 
		strncmp(test_array[i], test_array2[i], n[i]))
		{
			printf("4false\n");
		}
		
		/*testing StrSpn return size_t*/
		if (StrSpn(test_array[i], test_array2[i]) != strspn(test_array[i], 
		test_array2[i]))
		{
			printf("5false\n");
		}
		/*testing StrChr return ptr*/
		ptr1 = StrChr(test_array[i], c[i]);
		ptr2 = strchr(test_array[i], c[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("6false\n");
		}
		
		/*testing StrCpy return ptr*/
		ptr1 = StrCpy(empty_ptr, test_array2[i]);
		ptr2 = strcpy(empty_ptr, test_array2[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("7false\n");
		}
		
		/*testing StrnCpy return ptr*/
		ptr1 = StrnCpy(empty_ptr, test_array2[i], n[i]);
		ptr2 = strncpy(empty_ptr, test_array2[i], n[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("8false\n");
		}
		
		/*testing StrCat return pt*/
		ptr1 = StrCat(str, test_array2[i]);
		ptr2 = strcat(str, test_array2[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("9false\n");
		}
		
		/*testing StrnCat return pt*/
		ptr1 = StrnCat(str, test_array2[i], n[i]);
		ptr2 = StrnCat(str, test_array2[i], n[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("10false\n");
		}
		
		/*testing StrDup return ptr*/
		ptr1 = StrDup(test_array[i]);
		ptr2 = StrDup(test_array[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("11false\n");
		}
		free(ptr1);
		free(ptr2);
		
		/*testing StrStr return pt*/
		ptr1 = StrStr(test_array[i], test_array2[i]);
		ptr2 = strstr(test_array[i], test_array2[i]);
		if (strcmptest(ptr1,ptr2) != 0)
		{
			printf("12false\n");
		}
		
	}
	return 0;
}



