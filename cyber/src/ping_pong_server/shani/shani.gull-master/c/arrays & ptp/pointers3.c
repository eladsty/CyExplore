#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
int Josephus2(int n);
size_t ArrayLen(char arr[]); /* array length */
void **PrintEnv(char arr[]);
char *ToLower(char *c);
int *MatrixRow(int *arr, unsigned int row, unsigned int column, int *result);
void MainPrintSize();


int main()
{
	return 0;
}



/* ############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Michael         #*/
/* # description: this command #*/
/* # will sum up each          #*/
/* # rows in a matrix and      #*/
/* # return it as an array.    #*/
/* # return: array of row sums #*/
/* # special notes:            #*/
/* #############################*/

int *MatrixRow(int *arr, unsigned int row, unsigned int column, int *result)
{
	unsigned int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			*(result + i) += *((arr + i*column) + j);
		}
	}
	return result;
}



/* ############################*/
/* # Ex.2                      #*/
/* # status: approved          #*/
/* # reviewer: Nevo            #*/
/* # description: this command #*/
/* # will predict the index of #*/
/* # the last soldier standing #*/
/* # out of n soldiers.        #*/    
/* # arguments: integer.       #*/
/* # return: surviver's index. #*/
/* # special notes: index is   #*/
/* # n-1.                      #*/
/* #############################*/


int Josephus(int n)
{
	int i = 0;
	int *arr = (int*)malloc(sizeof(int)*n);
	for (; i < n; i++)
	{
		arr[i] = (i+1);
	}
	arr[n-1] = 0;
	i = 0;
	while (arr[i] != arr[arr[i]])
	{
		arr[i] = arr[arr[i]];
		i = (i+1) % n;
	}
	return arr[i];
}


/* #############################*/
/* # Ex.3                      #*/
/* # status: imple tested      #*/
/* # reviewer: Michael         #*/
/* # description: this command #*/
/* # will print the size of a  #*/
/* # data type run through it. #*/    
/* # arguments:                #*/
/* # literaly anything         #*/
/* # return: the length in     #*/
/* # bytes.                    #*/
/* # special notes:            #*/
/* ############################# */
union data_types
	{
	int a; 
	unsigned int b;
	signed int c; 
	long int d; 
	unsigned long int e;
	signed long int f; 
	short int g; 
	unsigned short int h;
	signed short int i; 
	char j;
	unsigned char k;
	signed char l;
	float o;
	double p;
	long double q;
	size_t y;
	};
	
void MainPrintSize()
{
	int j;
	union data_types i;
	for (j=0; j < 19; j++)
	{
		switch (j)
		{
			case 0:
				printf("the size of int type is: %zu\n", sizeof(i.a));
				break;
			case 1:
				printf("the size of unsigned int type is: %zu\n", sizeof(i.b));
				break;
			case 2:
				printf("the size of signed int type is: %zu\n", sizeof(i.c));
				break;
			case 3:
				printf("the size of long int type is: %zu\n", sizeof(i.d));
				break;
			case 4:
				printf("the size of unsigned long int type is: %zu\n", sizeof(i.e));
				break;
			case 5:
				printf("the size of signed long int type is: %zu\n", sizeof(i.f));
				break;
			case 6:
				printf("the size of short int type is: %zu\n", sizeof(i.g));
				break;
			case 7:
				printf("the size of unsigned short int type is: %zu\n", sizeof(i.h));
				break;
			case 8:
				printf("the size of signed short int type is: %zu\n", sizeof(i.i));
				break;
			case 9:
				printf("the size of char type is: %zu\n", sizeof(i.j));
				break;
			case 10:
				printf("the size of unsigned char type is: %zu\n", sizeof(i.k));
				break;
			case 11:
				printf("the size of unsigned char type is: %zu\n", sizeof(i.k));
				break;
			case 12:
				printf("the size of signed char type is: %zu\n", sizeof(i.l));
				break;
			case 15:
				printf("the size of float type is: %zu\n", sizeof(i.o));
				break;
			case 16:
				printf("the size of double type is: %zu\n", sizeof(i.p));
				break;
			case 17:
				printf("the size of long double type is: %zu\n", sizeof(i.q));
				break;
			case 18:
				printf("the size of size_t type is: %zu\n", sizeof(i.y));
				break;
			}
		}
}




/* #############################*/
/* # Ex.4                      #*/
/* # status: approved          #*/
/* # reviewer: Nave            #*/
/* # description: this command #*/
/* # will copy all of the      #*/
/* # enviroment variables into #*/
/* # a new buffer in lower case#*/ 
/* # and print them.           #*/    
/* # arguments: int argc,      #*/
/* # char *argv[], char *envp[]#*/
/* # return: 0 - success.      #*/
/* # special notes: memory leak#*/ 
/* # hazard.                   #*/
/* ############################# */

int MainEnv(int argc, char *argv[], char *envp[])
{
	char **envar = NULL;
	int i = 0;
	int counter = 0;
	for (; NULL != envp[counter]; counter++);
	envar = (char**)malloc(sizeof(size_t) * counter);
	for (; envp[i] != 0; i++)
	{
		envar[i] = ToLower(envp[i]);
		printf("%s\n\n", envar[i]);
	}
	free(envar);
	envar = NULL;
	return 0;
}
/* #############################*/
/* # Ex.4 sub func             #*/
/* #############################*/
char *ToLower(char *c)
{
	int i = 0;
	while (c[i] != '\0')
	{
		c[i] = (c[i] <= 'Z' && c[i] >= 'A') ? (c[i] + 32): c[i];
		++i;
	}
	return c;
}



