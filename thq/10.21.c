#include <stdio.h>
#include <stdlib.h>

void bsort(int *arr, int n);
void ptpsort1(int **arr, int n);

int main(void)
{
	int n, i;
	int *arr;
	
	printf("Enter n: ");
	scanf("%d", &n);
	arr = malloc(n * sizeof(int));
	for (i = 0; i < n; i++){
		scanf("%d", arr + i);
	}
	
	bsort(arr, n);
	ptpsort1(&arr, n);
	
	for (i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
}

/* bubble sotr */
void bsort(int *arr, int n)
{
	int i, j, t;
	for (i = 0; i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if (arr[j-1] > arr[j]){
				t = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = t;
			}
		}
	}
}

void ptpsort1(int **arr, int n)
{
	/* arr 不就是指向指针的指针 */
	bsort(*arr, n);
}
