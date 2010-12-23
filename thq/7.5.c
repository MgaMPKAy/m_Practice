#include <stdio.h>
#define N 9
int main(void)
{
    int arr[N] = {8, 6, 5, 4, 1, 0, 1, 2, 3};
    int i, j, t;

    for (i = 0, j = N - 1; i < j; i++, j--){
	t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
    }
	    
    for (i = 0; i < N; i++){
	printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
