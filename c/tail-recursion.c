#include <stdio.h>

long double fib(int n, long double acc1, long double acc2)
{
	return 1 == n ? acc1 : fib(n - 1, acc2, acc1 + acc2);
}

long double fac(int n, long double acc)
{
	return (1 == n)? acc : fac(n - 1, acc * n);
}

// You need gcc fib-tail.c -02
void forever()
{
	forever();
}

int main(void)
{
	printf("%Lf\n", fib(1000, 1, 1));
	printf("%Lf\n", fac(1000,1));
	forever();
	return 0;
}
