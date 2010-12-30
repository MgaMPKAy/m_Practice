#include <stdio.h>

int main(void)
{
	int arr[10], i, j, t;

	printf("Enter 10 int: ");
	for (i = 0; i < 10; i++)
		scanf("%d", arr + i);

	/* insertion */
	for (i = 9; i > 0; i--){
		if (arr[i] < arr[i-1]){
			t = arr[i-1]; arr[i-1] = arr[i];arr[i] = t;
		}
	}

	for(i = 2; i < 10; i++){
		t = arr[i];j = i - 1;
		while (j >= 1 && arr[j] > t){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = t;
	}

	/* print */
	for (i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}
