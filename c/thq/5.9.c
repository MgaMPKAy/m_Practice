#include <stdio.h>

int main(void)
{
	int arr[4], i, j, t;

	for (i = 0; i < 4; i++)
		scanf("%d", arr+i);

	for (i = 0; i <= 3; i++){
		for(j = 3; j > 0; j--){
			if(arr[j - 1] > arr[j]){
				t = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = t;
			}
		}
	}
	for (i = 0; i < 4; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}
