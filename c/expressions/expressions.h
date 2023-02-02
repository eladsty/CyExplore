void SayHello()
{
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n",0X22,0X48,0X65,0X6C,0X6C,0X6F,0X20,0X57,0X6F,0X72,0X6C,0X64,0X22);
}

float GivePower(int n)
{
	float x = 10;
	float result = 1;

	if ( n < 0 )
	{
		x = 1/10;
		n *= -1;
	}
	
	while( n > 0 )
	{
		result = result * x;
		n--;
	}
		
	return result;
}
 
 

