#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// #include <termios.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include "head_c.h"
#include "mylib.h"

void func_c(void)
{
	printf("create and use library:\n");
    welcome();
    outString("it's successful\n");
	printf("func_c\n");
}

