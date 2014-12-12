#include <stdlib.h>
#include <stdio.h>

struct test
{
	int a;
	int b;
};
int main()
{
	struct test test1;
	test1.a = 1;
	test1.b = 2;
	printf("a=%d\n",test1.a);
	printf("hello world!\n");
	return 0;
}
