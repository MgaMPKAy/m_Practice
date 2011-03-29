#include <stdio.h>

int min(int a, int b, int c)
{
	return a < b ?
		((a < c) ? a : c) :
	        ((b < c) ? b : c);
}

int main(void)
{
	int a[3];
	printf("Three Int Please: ");
	scanf("%d%d%d", a, a + 1, a + 2);

	printf("Min = %d\n", min(a[0], a[1], a[2]));
	return 0;
}
