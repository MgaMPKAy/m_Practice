#include <stdio.h>

int main(void)
{
	double x1 = 1, x2, a;
	
	printf("Enter a: ");
	scanf("%lf", &a);

	while (x2 -x1 > 1e-5  || x1 - x2 > 1e-5 ){
		x2 = 0.5 * (x1 + a / x1);
		x1 = x2;
		x2 = 0.5 * (x1 + a / x1);
	}

	printf("sqrt(%f) = %f\n", a, x2);
	return 0;
}
