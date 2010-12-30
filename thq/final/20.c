#include <stdio.h>


long  pascal(long  n, long r)
{
	if ((r == 1) || (r == n))
		return 1;
	else
		return  pascal(n - 1, r - 1) +  pascal(n - 1, r);
}

void draw_triangle(long n)
{
	int i, j, k;
	for(i = 0; i < n; i++){
		/* ident */
		for(k = 1; k < n - i; k++){
			printf("   ");
		}
		/* pacal */
		for(j = 0; j <= i; j++){
			printf("%6ld", pascal(i + 1, j + 1));
		}
		printf("\n");
	}
}

int main(void)
{
	long n;
	printf("Enter n: ");
	scanf("%ld", &n);

	draw_triangle(n);

	return 0;
}
