#include <stdio.h>

double fac(int n)
{
	static double r = 1;
	return r *= n;
}

int main(void)
{
	int i = 1;
	double y1, y2, t;
	double sum;

	sum = y1 = t = 1 / fac(i++);
	do {
		y2 = 1 / fac(i++);
		y1 = t;
		printf("y1 = %f\n", y1);
		printf("y2 = %f\n", y2);
	} while (t = y2, sum += y2, y1 - y2 > 10e-5);
	
	printf("Sum = %f\n", sum);
	
	return 0;
}
