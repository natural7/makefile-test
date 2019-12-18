#include "mylib.h"
#include <stdio.h>
 
void welcome(void)
{
	printf("welcome to libmylib\n");
}
 
void outString(const char *str)
{
	if(str != NULL)
	printf("%s\n", str);
}
