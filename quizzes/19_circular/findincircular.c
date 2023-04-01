int FindInCircular(int *arr, int len, int n)
{
	int start = 0, end = len-1, mid = len/2;
	
	while( arr[start] < arr[start+1] && start < len)
	{
	 	++start;
	 	end = start-1;
	}
	while(end != start)
	{
		if( arr[mid % len])
		arr[start];
	}
	
	
	
	
}

int main()
{


return 0;
}
