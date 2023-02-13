 
#include <stdlib.h> /* to use system*/
#include "IfelseKey.h"

 


int main()
{
	system("stty -icanon -echo");
	TOrA2();
	system("stty icanon echo");
	return 0;
}
   
 
