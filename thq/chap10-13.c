#include <stdio.h>

int main(void)
{
	int a, b;
	int *p, *q;
	
	scanf("%d %d", &a, &b);
	if (a < b)
		p = &a, q = &b;
	else
		p = &b, q = &a;

	printf("%d %d\n", *p, *q);

	return 0;
}
