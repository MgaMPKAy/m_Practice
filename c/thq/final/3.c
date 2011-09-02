#include <stdio.h>

int main(void)
{
	int n, i, j;
	double sum, fact;

	printf("Enter n: ");
	scanf("%d", &n);
	
	for (i = 1, sum = 0; i <= n; i++){
		for (j = 1, fact = 1; j <= i; j++){
			fact *= j;
		}
		sum += fact;
	}

	printf("1!+ ... + %d! = %f\n", n, sum);
	return 0;
}
