#include <stdio.h>
#define N 5

int main(void)
{
	int i, j;
	for (i = 0; i < 5; i++){
		for (j = i; j <(N-1); j++)
			printf("  ");
		for (j = 1; j <= i; j++)
			printf("%2d", j);
		for (; j >= 1; j--)
			printf("%2d", j);
		putchar('\n');
	}
	return 0;
}
