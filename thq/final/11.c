#include <stdio.h>
#define N 3
#define M 4
int main(void)
{
	int arr[N][M] = {{1, 4, 3, 4},
			 {5, 5, 5, 5},
			 {1, 4, 3, 4},};
	

	int i, j, t, max, min, sum = 0;
	
	for (i = 0; i < N; i++){
		/* find max of row */
		max = arr[i][0];
		for(j = 0; j < M; j++){
			if (arr[i][j] > max){
				max = arr[i][j];
			}
		}
		/* for each item == max in i row */
		for (j = 0; j < M; j++){
			if (arr[i][j] == max){
				/* find min of col */
				min = arr[0][j];
				for (t = 0; t < N; t++){
					if (arr[t][j] < min){
						min = arr[t][j];
					}
				}
				/* judege && print */
				if (max == min){
					printf("%d %d\n", i + 1 ,j + 1);
					sum++;
				}
			}
		}
	}
	printf("Total: %d\n",sum);
	return 0;
}
