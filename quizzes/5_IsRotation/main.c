int StrCmpInRotation(char *str1, char *str2, int n, int len)
{
	int i = 0;
	int j = 0;
	j = n;
	while('\0' != str1[i] && str2[j % len] == str1[i])
	{
		 ++i;
		 ++j;
	}
	
	if('\0' == str1[i] && strlen(str2) == len)
	{
		return 1;
	}
	
	return 0;
}
 
int IsRotation(char *str1, char *str2)
{
	int len = strlen(str1); 
	int n = 0; 

	while('\0' != str2[n])
	{
		if( str1[0] == str2[n])
		{
			 if(1 == StrCmpInRotation(str1,str2,n,len))
			 {
			 	return 1;
			 }
		}
		++n;
	}	
	
	 
	return 0;
}

int main()
{
	char *arr_match[] = {"abcde","deabc","cdeab","cdeab","cdeab" };
	char *arr_no_match[] = {"", "abcde","deaeebc","cdeeab","deacbd" };
	int i = 0;
 
	for(i = 0;i < 4 ; ++i)
	{
		printf("should be 1: %d\n",IsRotation(arr_match[i],arr_match[i+1]));
	}
	for(i = 0;i < 4 ; ++i)
	{
		printf("should be 0: %d\n",IsRotation(arr_no_match[i],arr_no_match[i+1]));
	}
 		printf("should be 0: %d\n",IsRotation("abcdefg","bcdefgabcde"));
	return 0;
}

