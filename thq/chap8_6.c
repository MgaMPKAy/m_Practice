#include <stdio.h>
#include <stdlib.h>

void tranform(int *arr, int n)
{
	int i, j, ni, nj;
	int *new_arr = malloc(n * n * sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			new_arr[i * n + j] = arr[i * n +j];
	for (j = n - 1; j >= 0; j--) {
		for(i = n - 1; i >= 0; i--) {
			ni = n - j - 1; nj = n - i - 1;
			arr[ni * n + nj] = new_arr[i * n + j];
		}
	}
	free(new_arr);
}

int main(void)
{
	int n, i, j;
	int *arr;
	
	printf("n = ");
	scanf("%d", &n);
	
	arr = malloc(n * n * sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &(arr[i * n + j]));
	
	tranform(arr, n);
	printf("-----------\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++){
			printf("%3d ", arr[i * n + j]);
		}
		printf("\n");
	}
	return 0;		
}
