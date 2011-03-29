#include <stdio.h>

#define N 6

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
	int arr[N];
	int i;

	printf("Input(%d): ", N);
	for (i = 0; i < N; i++)
		scanf("%d", arr + i);
	
	printf("Min = %d\n", min_r(arr, N));
	
	return 0;
}
