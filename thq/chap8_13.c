#include <stdio.h>
#include <stdlib.h>

int min_r(int arr[], int n)
{
	int min;
	if (n == 1)
		return arr[0];
	else {
		min = min_r(arr + 1, n - 1);
		return (min < arr[0])? min : arr[0];
	}
}

int main(void)
{
	int *arr;
	int i, n;

	printf("Num: ");
	scanf("%d", &n);
	arr = malloc(sizeof(int) * n);
	
	for (i = 0; i < n; i++)
		scanf("%d", arr + i);
	
	printf("Min = %d\n", min_r(arr, n));
	
	return 0;
}
