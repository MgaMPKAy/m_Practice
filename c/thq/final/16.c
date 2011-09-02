#include <stdio.h>

int func(int a, int b, int c, int d)
{
	float r;
	r = (float)(a * d - b * c)/(b * d);
	if (r > 0)
		printf("%d/%d > %d/%d\n", a, b, c, d);
	else if (r < 0)
		printf("%d/%d < %d/%d\n", a, b, c, d);
	else
		printf("%d/%d = %d/%d\n", a, b, c, d);
	return 0;
}

int main(void)
{
	int  a, b, c, d;
	printf("Enter a/b: ");
	scanf("%d/%d", &a, &b);
	printf("Enter c/d: ");
	scanf("%d/%d", &c, &d);

	func(a, b, c, d);
	return 0;
}
