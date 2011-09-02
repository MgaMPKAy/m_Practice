#include <stdio.h>

int main(void)
{
	int arr[5][6] = {{0, 1, 2, 3, 4, 5},
			 {1, 2, 3, 4, 5, 6},
			 {2, 3, 4, 5, 6, 7},
			 {3, 4, 5, 6, 7, 8},
			 {4, 5, 6, 7, 8, 9},};

	int i, j, m, n, t;
	/* insertion */
	for (m = 0; m < 5; m++)	{
		for(i = 1; i < 6; i++){
			t = arr[m][i];j = i - 1;
			while (j >= 0 && arr[m][j] < t){
				arr[m][j+1] = arr[m][j];
				j--;
			}
			arr[m][j+1] = t;
		}
	}
	/* print */
	for (m = 0; m < 5; m++){
		for (n = 0; n < 6; n++){
			printf("%d ", arr[m][n]);
		}
		printf("\n");
	}
	return 0;
}
