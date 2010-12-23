#include <stdio.h>

int main(void)
{
	int x, r;
	printf("Enter x: ");
	scanf("%d", &x);

	if (x < 1)
		r = x;
	else if (x >= 1 && x < 10)
		r = 2 * x - 1;
	else
		r = 3 * x -11;

	printf("%d\n", r);

	return 0;
}
