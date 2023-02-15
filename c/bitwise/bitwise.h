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

/* pfind mirror representation of a binary */
unsigned ByteMirror(unsigned N);



#endif
