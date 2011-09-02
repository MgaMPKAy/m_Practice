#include <stdio.h>

int wei, sum;
void count(long num)
{
	while (num  > 0) {
		wei++;
		sum += num % 10;
		num /= 10;
	}
	
}

int main(void)
{
	long num;

	printf("long num: ");
	scanf("%ld", &num);
	count(num);
	printf("Wei = %d, Sum = %d\n", wei, sum);

	return 0;
}
