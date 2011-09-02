#include <stdio.h>
#include <math.h>

int isprime(int num)
{
	int i, sq;
	sq = sqrt(num) + 1;
	for (i = 2; i < sq; i++){
		if (0 == num % i)
			return 0;
	}
	return 1;
}

int main(void)
{
	int n;
	printf("Enter a int:");
	scanf("%d", &n);
	if (isprime(n))
		printf("Prime\n");
	else
		printf("Not Prime\n");
	
	return 0;
}
