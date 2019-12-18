#include "mylib2.h"
#include <stdio.h>
 
void welcome2(void)
{
	printf("welcome to libmylib\n");
}
 
void outString2(const char *str)
{
	if(str != NULL)
	printf("%s\n", str);
}
