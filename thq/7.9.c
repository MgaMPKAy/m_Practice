#include <stdio.h>
#define N 15

int main(void)
{
	int arr[N], i, j, n;

	for (i = 0; i < N; i++){
		arr[i] = 2 * (15 - i);
	}

	printf("Enter a num:");
	scanf("%d", &n);

	if ( n > arr[0] || n < arr[N-1]){
		printf("No\n");
		return 0;
	}
	for (i = 0, j = N - 1; i < j;){
		if (n > arr[(i + j) / 2])
			i = (i + j) / 2;
		else if (n < arr[(i + j) /2])
			j = (i + j) / 2;
		else
			break;
	}

	if (n == arr[(i+j)/2])
		printf("%d\n", arr[(i+j)/2]);
	return 0;
}
