/* This function appand to the file a new line
**	status:		Approved 
**	reviewer:	Amir
**	args:		two char pointers
**	return:		enum RETURN with the corresponding error code or 0 for success
*/




#include "files.h" /*decleration of my functions*/
#include <stdio.h> /* to use printf and for file related funcitons and to remove*/
#include <assert.h> /*to use assert*/
#include <string.h>/* for strcmp */
#include <stdlib.h>/* to use exit */



void Print(int x)
{
	printf("My int is: %d \n",x);
}


void PrintStruct()
{
	int i = 0;

	struct print_me 
	{
		int x;
		void(*p_func)(int);
	};

	struct print_me arrayOfStructs[10];

	while (i < 10)
	{	 
		arrayOfStructs[i].x = i; 
		arrayOfStructs[i].p_func = &Print;
		arrayOfStructs[i].p_func(arrayOfStructs[i].x);
		++i;
	}

}
 
 

enum RETURN WriteToFile(char *file_name)
{
	size_t n = 100;
	char myBuffer[100];
 	FILE *file_p = NULL;
	assert(NULL != file_name);

 
 	file_p = fopen(file_name,"a");
 	fgets(myBuffer,n, stdin);  
	fputs(myBuffer, file_p);
	
	fclose(file_p);
	
	return SUCCESS;
}

enum RETURN Append(char *file_name, char *str)
{
 	FILE *file_p = NULL;
 	file_p = fopen(file_name,"a");
	fputs(str, file_p);
	fclose(file_p);
	return SUCCESS;
}

enum RETURN Prepend(char *file_name, char *str) 
{
	char c;
	FILE *file_p = NULL;
	FILE *temp_file = NULL;
	temp_file = fopen("tempFile", "a");
	fputs(++str, temp_file);
	
	file_p = fopen(file_name, "r");

	while(EOF != (c = fgetc(file_p)))
	{
		fputc(c, temp_file);
	}

	fclose(file_p);
	remove(file_name);
 
	fclose(temp_file);
 	rename("tempFile",file_name);
 	
 	return SUCCESS;
}


enum RETURN Remove(char *file_name, char *str)
{
  	remove(file_name);
  	return REMOVE;
}

enum RETURN Count(char *filename, char *str)
{
 	size_t lineCnt = 0;
	char c; 
	FILE *file_p;
	file_p = fopen(filename,"r");
 
	while(EOF != (c = fgetc(file_p)))
	{
		if('\n' == c)
		{
			++lineCnt;
		}
	}
	printf("The number of lines: %lu\n", lineCnt);
	
	return SUCCESS;
}
 
 
enum RETURN Exit(char *filename, char *str) 
{
	exit(0);
	return SUCCESS;
}

int WriteSuccessfully(const char *str1, const char *str2)
{
 
	return SUCCESS;
}

int TestPrepend(const char *str1, const char *str2)
{
	if('<' == *str2)
	{
		return 0;
	}
	
	return 1;
}



void FWriteSpecial(char *file_name)
{
	int i = 0;
	int n = 100;	
	char myBuffer[100];
 
 
	struct caseStruct
	{
		char *string;
		int(*p_strcmp)(const char*, const char*);
		enum RETURN(*p_DoSpecial)(char*, char*);
	};
	
	struct caseStruct arr[5] = 
	{	 
		{"-remove\n", &strcmp, &Remove},
		{"-count\n", &strcmp, &Count},
		{"-exit\n", &strcmp, &Exit},
		{"<", &TestPrepend, &Prepend},
		{"", &WriteSuccessfully ,&Append}
	};  
	
 	 
	 while(1)
	 {
	 	fgets(myBuffer,n, stdin); 
	 	for(i=0; i<5; ++i)
	 	{
	 		if(0 == arr[i].p_strcmp(arr[i].string, myBuffer))
	 		{
	 			arr[i].p_DoSpecial(file_name ,myBuffer);
	 			break;
	 		}
	  
	 	}
	 	i = 0;
	 }

}



 
