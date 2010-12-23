#include <stdio.h>

int main(void)
{
	int a, b, c;
	printf("Enter a b c: ");
	scanf("%d %d %d", &a, &b, &c);

	if (a > b && a > c)
		printf("%d\n", a);
	else if (b > c)
		printf("%d\n", b);
	else
		printf("%d\n", c);

	return 0;
}
