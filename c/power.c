double power_3(int x, int n)
{
	double r = 1;
	for (;;) {
		if (n == 0) return r;
		if (n == 1) return r * x;
		if (n % 2 != 0) r *= x;
		x *= x;
		n /= 2;
	}
}

double power_2(int x, int n, double r)
{
	if (n == 0) return r;
	if (n == 1) return r * x;
	if (n % 2 != 0) r *= x;
	return power_2(x * x, n / 2, r);
}

double power_1(int x, int n)
{
	if (n == 0) {
		return 1;
	} else if (n % 2 == 0) {
		return power_1(x * x, n / 2);
	} else {
		return x * power_1(x * x, n / 2);
	}
}

double power_0(int x, int n)
{
	if (n == 0)
		return 1;
	else
		return x * power_0(x, n - 1);
}

// Test
#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("%f\n", power_0(4, 10));
	printf("%f\n", power_0(4, 11));

	printf("%f\n", power_1(4, 10));
	printf("%f\n", power_1(4, 11));

	printf("%f\n", power_2(4, 10, 1));
	printf("%f\n", power_2(4, 11, 1));

	printf("%f\n", power_3(4, 10);
	printf("%f\n", power_3(4, 11));

	return 0;
}
