#include <stdio.h>

int findmax(int arr[])
{
	int i, max;
	for (i = 0, max = *arr; i < 10; i++) {
		if (*(arr + i) > max) {
			max = *(arr + i);
		}
	}
	return max;
}

int main(void)
{
	int arr[10], i;

	for (i = 0; i < 10; i++) {
		scanf("%d", arr + i);
	}
	printf("max = %d\n", findmax(arr));
	
	return 0;
}
