 #include <stdio.h>
 
 
 
int MaxSubArray(int arr[], unsigned len)
{
  int max_sum = 0;
  int current_sum = 0;
  unsigned i = 0;
	
  for(i=0; i < len; ++i) 
  {
    current_sum = current_sum + arr[i];
    
    if (current_sum < 0)
    {
          current_sum = 0; 
    }
 
    if(max_sum < current_sum)
    {	
      max_sum = current_sum;
	}
}

return max_sum;
}



int main()
{ 
		/*"should be 3,6 and 8 "*/
	int array[] = {-2,1,-3,4,-1,2,3,-5,4};

	
	printf(" sum is %d",MaxSubArray(array,9));
	
	return 0;
}













/*


/*
	int start_i = 0, end_i = 0, max_sum = 0, temp_sum;
  	unsigned i = 0 , j = 0;
	
	while(i < len);
	{
 		
 		if(arr[i] >= 0)
 		{
	 		if(arr[i] > temp_sum)
	 		{
	 			max_sum = arr[i];
	 			start_i = i;
	 			end_i = i;
	 		}
 		}
 		
 		++end_i;
 		++i;
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
	
/*
 arr[start_i] + (end_i == start_i ? 0 : arr[end_i]);

	printf("should be 3,6 and 8.\ni1 is: %d, i2 is: %d, sum is:%d \n", max_i1, max_i2, max_sum); */
 	
	

 
