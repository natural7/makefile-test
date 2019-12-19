#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <pthread.h>
#include "head_a.h"
#include "head_c.h"
#include "mylib2.h"
#include "head_b_1.h"

int main(int argc, const char *argv[])
{
	printf("main\n");
	func_a();
	func_c();
	outString2("lib2 test");
	func_b_1();
	return 0;
}
