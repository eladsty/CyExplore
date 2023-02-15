#ifndef __STRINGS_H__
#define __STRINGS_H__

/* x*(2^y) */
long Pow2(unsigned int x, unsigned int y);

/* check if n is power of 2 */
int IsSquared(unsigned int n);

/* check if n is power of 2 wihtout a loop*/
int IsSquaredNoLoop(unsigned int n);

/* add one with bitwise*/
int AddOne(int x);

/* print from array only numbers that have 3 1's */
void ThreeBitsOn(const unsigned arr[], unsigned n);

/* find mirror representation of a binary with loop*/
unsigned ByteMirror(unsigned N);

/* find mirror representation of a binary without loop*/
unsigned char ByteMirrorNoLoop(unsigned char);

/* check if both the second and the 6th bit is on (1) */
unsigned IsBothOn(unsigned char);

/* swap between the 3rd and 5th bits and return new number*/
unsigned SwapBits(unsigned num);

/* closest smaller number that is devisible by 16 without remainder*/
unsigned Divisible16(unsigned num);


#endif
