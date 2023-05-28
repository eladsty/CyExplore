#include <stdio.h> /* for printf() and getchar() */
#include <stdlib.h> /* for system() */

#include "functions.h" /*connect to header file */





//* ############################*/
/* # Ex.1                      #*/
/* # status: imple tested      #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will take input from user #*/
/* # and print specific notes  #*/
/* # for A, T and esc chars    #*/
/* # special notes: first      #*/
/* # instance if/else, second  #*/
/* # instance switch/case,     #*/
/* # third instncr LUT         #*/
/* #############################*/
void IfElseKey()
{
	char key;
	system("stty -icanon -echo");
	
	while (1)
	{
		key = getchar();
		
		if ( 65 == key )
		{
			printf("A-pressed\n");
		}
		
		else if ( 84 == key)
		{
			printf("T-pressed\n");
		}
		
		else if ( 27 == key )
		{
			system("stty icanon echo");
			return;
		}
	}

}

void SwitchKey()
{
	char key;
	system("stty -icanon -echo");
	
	while (1)
	{
		switch(key = getchar())
		{
			case (65):
			{
				printf("A-pressed\n");
				continue;
			}
			
			case (84):
			{
				printf("T-pressed\n");
				continue;
			}
			
			case (27):
			{
				system("stty icanon echo");
				return;
			}
			
			default:
			{
				continue;
			}
		}
	}
}




void APressed()   /*this func will print */
{
	printf("A-pressed");
}

void TPressed()   /*this func will print */
{
	printf("T-pressed");
}

void Esc()  /*this func will terminate */
{
	system("stty icanon echo");
	exit(0);
}

void Nulled() /*this func will insert 0 into any value passed */
{
}

void LutKey()
{
	typedef void (*ptr_to_fun)(void);
	char key;
	int i = 0;
	ptr_to_fun arr[256];
	system("stty -icanon -echo");

	while (i++ < 256)
	{
		arr[i] = Nulled;
	}
	
	arr[27] = Esc;
	arr[65] = APressed;
	arr[85] = TPressed;
	
	while (1)
	{
		key = getchar();
		(*arr[(unsigned char)key])();
	}
}
