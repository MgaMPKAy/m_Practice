#include <stdio.h>

int main(void)
{
	long  sq_of_sum = 0, sum_of_sq = 0;
	int i;

	for (i = 1; i <= 100; i++)
		sq_of_sum += i * i;
	for (i = 1; i <= 100; i++)
		sum_of_sq += i;
	sum_of_sq = sum_of_sq * sum_of_sq;

	printf("%ld\n", sum_of_sq - sq_of_sum);
	return 0;
}
