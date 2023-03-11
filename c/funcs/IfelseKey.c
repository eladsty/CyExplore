#ifndef __IFELSEKEY_H_CR4__
#define __IFELSEKEY_H_CR4__

/* This function prints A-Pressed!.
**	status:		approved
**	reviewer:	Amir
**	args:		void
**	return:		void	
*/


typedef void(*table)(void);

#include <stdio.h>  /* to use printf*/
#include <stdlib.h> /*for exit(0)*/
#include "IfelseKey.h" /* my function decleration*/


void IfPrintAorT()
{
	char c;
	while(27 != c)
	{

		c = getchar();
		if('A' == c)
		{
			printf("A Pressed");			
		}
		else if('T' == c)
		{
			printf("T Pressed");
		}

		else if(27 == c)
		{
			exit(0);
		}
		else
		{
			printf("\n");				
		}

		}
}

void TOrA1()
	{
		char c;
		while(27 != c)
		{
	 
		c = getchar();
		switch(c) 
		{
			case 'A':
				printf("A Pressed");
				break;
			case 'T':
				printf("T Pressed");
				break;
			default:
				printf("\n");
		}
		}
	}
void CharA()
{
	printf("A was pressed\n");
}

void CharT()
{
	printf("T was pressed\n");
}

void Esc()
{
	exit(0);
}

void EmptyFunc()
{
	/*do nothing, for the other characters*/
}

void TOrA2()
{
	int i = 0;
	
	table letter_func_table[128];
	
	while(i < 128)
	{
		letter_func_table[i] = EmptyFunc;
		++i;
	}
	
	letter_func_table['A'] = CharA;
	letter_func_table['T'] = CharT;
	letter_func_table[27] = Esc;
	
	while(1)
	{
		letter_func_table[getchar()]();
	}
}


 #endif	/* __IFELSEKEY_H_CR4__ */

 
 
