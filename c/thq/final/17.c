#include <stdio.h>
#define N 10

void insertion(int arr[], int l, int r)
{
	int i, j, t, k;
	for(i = r; i > l; i--){
		if (arr[i]< arr[i-1]){
			t = arr[i-1]; arr[i-1] = arr[i]; arr[i] = t;
			for (k = l; k <= r; k++){
				printf("%d ", arr[k]);
			}
			printf("\n");
		}
	}
	
	for(i = l + 2; i <= r; i++){
		t = arr[i];j = i - 1;
		while (j >= 1 && arr[j] > t){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = t;
		for (k = l; k <= r; k++)
			printf("%d ", arr[k]);
		printf("\n");
	}
}

int main(void)
{
	int arr[N] = {8, 6, 5, 4, 1, 0, 1, 2, 3, 4};
	int i;

	for (i = 0; i < N; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	insertion(arr, 0, 9);
	
	for (i = 0; i < N; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
