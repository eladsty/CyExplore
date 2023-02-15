#ifndef __FILES_H__CR4__
#define __FILES_H__CR4__


#include <stdio.h> /* to use FILE*/

enum RETURN {SUCCESS, CLOSE, COUNT, FAIL, REMOVE};


/*function that print numbers*/
void Print(int n);

/*create struct's array and print them */
void PrintStruct();

/* receive name of file, open it, append the string to the end and close it.*/
enum RETURN WriteToFile(char *file_ptr);

/* delete file */
enum RETURN Remove(char *file_name, char *str);

/* count number of lines*/
enum RETURN Count( char *filename, char *str);

/* exit the program */
enum RETURN Exit(char *filename, char *str); 

/* add to the beginning */
enum RETURN prepend(char *file_name, char *str);

/* add to end */
enum RETURN append(char *file_name, char *str);

/* return 0 */
int WriteSuccessfully(const char *str1, const char *str2);

/* check for <*/
int TestPrepend(const char *str1, const char *str2);

 
  

 
#endif 
  
