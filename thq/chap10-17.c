#include <stdio.h>

int main(void)
{
	int arr[10] = {1, 3, 5, 0, 1,
		       2, 1, 2, 0, 4,};

	int min, i;
	
	for (i = 1, min = arr[0] + arr[i] +arr[2]; i < 9; i++) {
		if (arr[i] + arr[i - 1] + arr[i + 1] < min)
			min = arr[i] + arr[i - 1] + arr[i + 1];
	}
	printf("min = %d\n", min);

	return 0;
}
