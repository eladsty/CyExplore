 
#include <stdlib.h> /* to use system*/
#include "IfelseKey.h"

 


int main()
{
	system("stty -icanon -echo");
IfPrintAorT();
	system("stty icanon echo");
	return 0;
}
   
 
