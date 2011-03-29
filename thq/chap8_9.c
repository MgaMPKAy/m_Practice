#include <stdio.h>

long func(long n)
{
	int last = n % 10;
	
	if (n < 10 && last % 2 == 0)
		return last;
	if (last % 2 == 0)
		return last + 10 * func(n / 10);
	else
		return func(n / 10);
}

int main(void)
{
	long num;

	printf("long int num = ");
	scanf("%ld", &num);

	printf("Result: %ld\n", func(num));
	
	return 0;
}
