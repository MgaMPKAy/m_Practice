#include <stdio.h>

double mul(int n)
{
	if (n < 1)
		return 0;
	else
		return n * (n + 1) * (n + 2) + mul(n - 2);
}

int main(void)
{
	int n;

	printf("N = ");
	scanf("%d", &n);
	if (0 == n % 2) {
		printf("ERROR, n shoule be 1 3 5 7 9 ...(2k + 1)\n");
		return 1;
	}
	printf("%.0f\n", mul(n));

	return 0;
}
