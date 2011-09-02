#include <stdio.h>

int main(void)
{
	long num;
	int sum;
	
	printf("Enter a (long) int: ");
	scanf("%ld", &num);

	if (num < 0)
		num = -num;
	for (sum = 0; num >= 10; num /= 10)
		sum += num % 10;
	sum += num;

	printf("Sum = %d\n", sum);

	return 0;
}
