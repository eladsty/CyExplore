
#include <stdio.h> /*functions in c will use this lib */
#include "files.h" /* link w header */
#include "files.c" /*easier to compile */

int main()
{
	/*PrintArr();*/
	/*char c[100];*/
	/*fgets(c, 100, stdin);*/
	/*WriteToFile("files.txt");*/
	FWriteSpecial("files.txt");
	return 0;
}



