#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n, sum, *arr;

	scanf("%d", &n);
	arr = malloc(sizeof(int) * n);
	for (sum = 0; n > 0; n--) {
		scanf("%d", arr + n);
		sum += *(arr + n);
	}
	printf("Sum = %d\n", sum);

	return 0;
}
