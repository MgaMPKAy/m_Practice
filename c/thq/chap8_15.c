#include <stdio.h>
#define M 4
#define N 4
int main(void)
{
	int a[M][N] = {{1, 2, 3, 4},
		       {5, 6, 7, 8},
		       {9, 10, 11, 12},
		       {13, 14, 15, 16}};
	
	int b[M][N] = {{0, 0, 0, 1},
		       {0, 0, 0, 2},
		       {0, 0, 0, 0},
		       {0, 0, 0, 0}};
	int i, j;

	for (i = 0; i < M * N; i++) {
		for (j = 0; j < M * N; j++) {
			if ((int *)a[i] == (int *)b[j]) {
				printf("YES\n");
				return 0;
			}
		}
	}
	printf("NO");
	return 0;
}
