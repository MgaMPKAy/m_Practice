#include <stdio.h>
#define N 10

int main(void)
{
	int i, j, l, r;
	int arr[N + 1] = {0};
	
	arr[0] = 1;
	for (i = 0,j = 0; i < N ; i++){
		while (arr[j] != 0){
			printf("%d ", arr[j++]);
		}
		printf("\n");
		for (j = 1, l = arr[0]; j <= i + 1; j++){
			r = arr[j];
			arr[j] = l + r;
			l = r;
		}
		j = 0;
	}
	return 0;
}
