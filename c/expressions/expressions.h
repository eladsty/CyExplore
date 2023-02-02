void SayHello()
{
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n",0X22,0X48,0X65,0X6C,0X6C,0X6F,0X20,0X57,0X6F,0X72,0X6C,0X64,0X22);
}

float GivePower(int n)
{
	float base = 10;
	float result = 1;

	if ( n < result )
	{
		base = 1/base;
		n *= -1;
	}
	
	while( n > 0 )
	{
		result *= base;
		n--;
	}
		
	return result;
}
 

int FlipDigits(int n)
{

	int flipped = 0;

	while( n > 0 )
	{
		flipped = flipped * 10;
		flipped += n%10;
		n /= 10;
	}

	return flipped;
}

void SwapValues(int *a, int *b)
{
	int temp = *a;
	assert( a != NULL && b != NULL );
	*a = *b;
	*b = temp;
}
