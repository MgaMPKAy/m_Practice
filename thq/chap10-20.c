#include <stdio.h>

int max_cd(int m, int n)
{
	if (n == 0)
		return m;
	return max_cd(n, m % n);
}

int main(void)
{
	int a, b;

	scanf("%d %d", &a, &b);

	printf("gcd = %d\n",  max_cd(a, b));
		
	return 0;
}
