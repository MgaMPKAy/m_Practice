#include <stdio.h>

int main(void)
{
	float x, y;
	float a, b, c, d;

	printf("Enter x y:");
	scanf("%f %f", &x, &y);

	a = (x - 2) * (x - 2) + (y - 2) * (y - 2);
	b = (x + 2) * (x + 2) + (y + 2) * (y + 2);
	c = (x - 2) * (x - 2) + (y + 2) * (y + 2);
	d = (x + 2) * (x + 2) + (y - 2) * (y - 2);

	if (a < 1 || b < 1 || c < 1 || d < 1)
		printf("10m\n");
	else
		printf("0m\n");

	return 0;
}
