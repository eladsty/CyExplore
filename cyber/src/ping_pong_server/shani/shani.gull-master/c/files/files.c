#include <stdio.h> /* for printf and file commands */

#include "files.h" /* to link with header */
#include <stdlib.h> /*for struct */



struct print_me
{
	int num;
	void (*print)(int);
};

void Print(int num)
{
	printf("%d\n", num);
}

/* #############################*/
/* # Ex.1                      #*/
/* # status: imple tested      #*/
/* # reviewer:                 #*/
/* # description: this command #*/
/* # will declare array of type#*/
/* #  struct defined proir to  #*/
/* # this sunction, and print  #*/
/* # the values of it's first  #*/
/* # member using it's second  #*/
/* # member.                   #*/
/* # special notes:            #*/
/* #############################*/
	
void PrintArr()
{
	int i = 0;
	struct print_me arr[10];
	for (; i < 10; i++)
	{
		arr[i].num = i;
		arr[i].print = &Print;
		arr[i].print(arr[i].num);
	}
}

/* ############################*/
/* # Ex.2 phase 1              #*/
/* # status: imple tested      #*/
/* # reviewer:                 #*/
/* # description: this command #*/
/* # will recieve input from   #*/
/* # user and append it to end #*/
/* # of file given as argument #*/
/* # special notes:            #*/
/* #############################*/

void WriteToFile(char *file_name)
{
	char c[100];
	FILE *file;
	file = fopen(file_name, "a+");

	fgets(c, 100, stdin); /* return arr */
	if (sizeof(c) < 100)
	{
		fputs(c, file);
	}
	else
	{
		printf("input is too long\n");
	}
	fclose(file); /*return 0 success els EOF */
}

/* ############################*/
/* # Ex.2 phase 2              #*/
/* # status:  psaudu done      #*/
/* # reviewer:                 #*/
/* # description: this command #*/
/* # will recieve input from   #*/
/* # user and append it to end #*/
/* # of file given as argument #*/
/* # special notes:            #*/
/* # -remove(deletes the file),#*/
/* # -count(return num of lines#*/
/* # in file),                 #*/
/* # -exit(terminates),        #*/
/* # <(append to start)        #*/
/* #############################*/

enum Test {success, fail};

int StrCmp(char *arr1, char *arr2)
{
	while (*arr1 == *arr2 && ('\0' != *arr1 ))
	{
		++arr1;
		++arr2;
	}
	return (*arr1 - *arr2);
}
enum Test ExitProg(char *file, char *str)
{
	exit(-1);
	return success;
}

enum Test RemoveFile(char *file, char *str)
{
	remove(file);
	exit(-1);
	return success;
}

enum Test Count(char *file, char *str)
{
	char c;
	int count = 0;
	FILE *temp;
	temp = fopen(file, "r");
	for (c = getc(temp); c != EOF; c = getc(temp))
	{
		if (c == '\n')
		{
			++count;
		}
	}
	printf("%d\n", count);
	return success;
}

int FisrtChr(char *str, char *buffer)
{
	return (*str == *buffer ? 0 : 1);
}

int IsSpecial(char *str, char *buffer)
{
	return 0;
}

enum Test AppendStr(char *file, char *buffer)
{
	FILE *temp;
	temp = fopen(file, "a+");
	fputs(buffer, temp);
	return success;
}

enum Test PreAppend(char *file, char *buffer)
{
	FILE *new_file, *temp;
	char c;
	new_file = fopen("new_file.txt", "w");
	temp = fopen(file, "r");
	
	++buffer;
	fputs(buffer, new_file);
	c = fgetc(temp);
	
	while (c != EOF)
	{
		fputc(c, new_file);
		c = fgetc(temp);
	}
	fclose(temp);
	fclose(new_file);
	remove(file);
	rename("new_file.txt", file);
	return success;
}


struct options
{
	char *str;
	int (*ptr_strcmp)(char*, char*); /*ptr to strncmp */
	enum Test (*ptr_op)(char *, char *str);
};



void FWriteSpecial(char *file_name)
{
	int i;
	char c[1024];
	
	struct options arr[5] = {
		{"-remove\n", StrCmp, RemoveFile},
		{"-count\n", StrCmp, Count},
		{"-exit\n", StrCmp, ExitProg},
		{"<", FisrtChr, PreAppend},
		{"", IsSpecial, AppendStr}
	};

	FILE *file;
	
	while (1)
	{
		
		file = fopen(file_name, "a+");
		if (NULL == file)
		{
			printf("oopsie..");
			break;
		}

		fgets(c, 1024, stdin); /* get input */
		
		
		for (i = 0; i < 5; i++)
		{
			if (!(arr[i].ptr_strcmp(arr[i].str, c)))
			{
				arr[i].ptr_op(file_name, c);
				break;
			}
		}
		
		fclose(file); /*return 0 success else EOF */
	}
}




