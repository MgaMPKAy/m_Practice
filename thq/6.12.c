#include <stdio.h>
#include <math.h>

float f(float x)
{
	return 2 * x * x * x - 4 * x * x + 3 * x - 6; 
}

float derive(float x)
{
	return (f(x+0.0001) - f(x)) / 0.0001;
}

int main(void)
{
	float  x1 = 1.5, x2;;
	
	for (;;){
		x2 = x1;
		x1 = x2 - f(x2) / derive(x2);
		if (fabs(x1 - x2) < 1e-6)
			break;
	}
	printf("%f\n", x2);
	
	return 0;
}
