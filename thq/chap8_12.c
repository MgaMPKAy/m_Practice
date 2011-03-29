#include <stdio.h>
#include <math.h>

double func_y(double x, int n)
{
	double result;
	if (n == 1) {
		return x;
	} else {
		result = sqrt(x) * (1 - func_y(x, n - 1));
		if (result < 0)
			return -result;
		else
			return result;
	}
}

int main(void)
{
	double x, n;

	printf("x = :");
	scanf("%lf", &x);
	printf("n = :");
	scanf("%lf", &n);

	printf("y = %f\n", func_y(x, n));

	return 0;
}
	
