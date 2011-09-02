#include <stdio.h>

double fact(int n)
{
	int i;
	double s = 1;
	for (i = 1; i <= n; i++)
		s *= i;
	return s;
}

double combine(int n, int m)
{
	if (m > n)
		return 0;
	else if (n == 1 && m == 1)
		return 1;
	else if (m == 1)
		return n;
	else
		return fact(n) / ( fact(n - m) * fact(m));
}

int main(void)
{
	int n, m;
        double c;
	printf("Enter n m:");
	scanf("%d %d", &n, &m);

	c = combine(n, m);
	printf("C(%d, %d) = %.0f\n", n, m, c);

	return 0;
}
