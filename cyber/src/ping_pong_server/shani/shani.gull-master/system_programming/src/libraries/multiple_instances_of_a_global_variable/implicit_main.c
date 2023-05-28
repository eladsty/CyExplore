
#include "staticlib.h"
#include "dynamiclib1.h"
#include "dynamiclib2.h"

int main(void)
{

	PrintGlobalVariableAddress();
	foo();
	foo2();
	return 0;
	
}

