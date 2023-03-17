#include <string.h>
#include <stdio.h>


int IsRotation(char *str1, char *str2)
{
	char len = strlen(str2); 
	char *str2_start = str2;

	while('\0' != *str2_start)
	{
		
		if(*str2_start == *str1)
		{
			
		}
		 c = *
		++str2_start;
		
	}	
	if(strstr(str1 ,(str2 + i)))
	{
	  break;
	}
	
	}
	
	str2 = str2 + i;
	i = 0;
	
	for(; '\0' != *(str1 + i); ++i ,++j)
	{
	if(!(*(str2 + j)))
	{
	  str2 = str2_start;
	  j = 0;
	}
	if(*(str1 + i) != *(str2 + j))
	{
	  return 0;
	}
	}
	return *(str1 + i) == *(str2 + i);
	}

}

int main()
{

	return 0;
}
