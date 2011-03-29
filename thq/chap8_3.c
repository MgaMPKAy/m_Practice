#include <stdio.h>
#include <math.h>

int is_prime(int num)
{
	int i, sq;
	sq = sqrt(num) + 1;
	for (i = 2; i < sq; i++){
		if (0 == num % i)
			return 0;
	}
	return 1;
}

void split(int a)
{
	int i, j;
	for (i = 2, j = a - i; i < a && j >= i; i++) {
		j = a - i;
		if (is_prime(i) && is_prime(j)) {
			printf("%3d = %3d + %3d\n", a, i, j);
		}
	}
}

int main(void)
{
	int n;
	printf("A Even: ");
	scanf("%d", &n);
	if (n % 2 != 0) {
		printf("Not a even number\n");
		return 1;
	}
	split(n);
	return 0;
}
