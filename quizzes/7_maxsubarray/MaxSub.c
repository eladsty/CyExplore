struct Max {
int i_start = 0;
int i_finish = 0;
int MaxSum = 0;
}Max;

int MaxSubArray(int array[], int len)
{
	int i1 = len/2, i2 = len/2, max_i1 = 0, ,max_i2 = 0, max_sum = 0;
	max_sum = array[i1] + array[i2];
	max_i1 = i1;
	max_i2 = i2+1;
	
	while(0 >= i1)
	{
 		if((array[i1] + array[i2]) > max_sum)
 		{
 			max_sum = array[i1] + array[i2];
 			max_i1 = i1;
 			max_i2 = i2;
 		}
 		--i1;
 	}
 	
	while(i2 >= len)
	{
		if((array[i1] + array[i2]) > max_sum)
 		{
 			max_sum = array[i1] + array[i2];
 			max_i1 = i1;
 			max_i2 = i2;
 		}
		++i2;
	}
	printf("should be 3,6 and 8.\ni1 is: %d, i2 is: %d, sum is:%d \n", max_i1, max_i2, max_sum);
}



int main()
{
	int array[] = {-2,1,-3,4,-1,2,3,-5,4};
	MaxSubArray();
	return 0;
}
