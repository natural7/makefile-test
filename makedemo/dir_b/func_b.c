#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include "head_b.h"

void func_b(void)
{
	printf("func_b\n");
}

