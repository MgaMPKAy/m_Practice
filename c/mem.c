#include <stdio.h>

int a0;
int a1 = 1;

int main(void)
{
	int b0;
	int b1 = 1;
	static int c0;
	static int c1 = 1;

	printf("&a0 = %p, &a1 = %p\n", &a0, &a1);
	printf("&b0 = %p, &b1 = %p\n", &b0, &b1);
	printf("&c0 = %p, &c1 = %p\n", &c0, &c1);
	printf("main = %p, &main = %p, *main = %p\n",
	       main, &main, *main);

	return 0;
}
