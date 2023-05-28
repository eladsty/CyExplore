#include "bitwise.h" /* function declaration */


int main()
{
	unsigned int arr[] = {1, 7, 52, 4, 5, 6};
	int x = 3, y = 5;
	printf("pow 2: %ld\n", pow2(2,2));
	printf("is square no loop: %d\n", IsSquaredNoLoop(0));
	printf("is square loop: %d\n", IsSquared(0));
	printf("add one: %d\n", AddOne(-15));
	printf("byte mirror: %d\n", ByteMirror(15));
	printf("byte mirror no loop: %d\n", ByteMirrorNoLoop(0));
	ThreeBitsOn(arr, 6);
	printf("is both on: %d\n", IsBothOn(35));
	printf("is both on: %d\n", IsBothOn('p'));
	printf("is one on: %d\n", IsOneOn(7));
	printf("is one on: %d\n", IsOneOn('Y'));
	printf("swap of Y is M(77): %d\n", SwapBits('Y'));
	printf("devisible by 16 and smaller than 53: %d\n", Divisible16(4890));
	Swap(&x, &y);
	printf("count set bits: %d\n", CountSetBits(30));
	printf("count set bits: %d\n", CountSetBitsNoLoop(30));
	printf("float as bits: %d\n", FloatAnalysis(19.6));
	return 0;
}

