#include <stdio.h>
#define N 15

int main(void)
{
	int arr[N], i, j, n, m, flag = 0;

	for (i = 0; i < N; i++){
		arr[i] = 2 * (15 - i);
	}

	printf("Enter a num:");
	scanf("%d", &n);
	
	//for (i = -1, j = N - 1; j - i > 1; ){}
	i = 0; j = N - 1;
	while (i <= j) {
		m = (i + j) / 2;
		if (n == arr[m]){
			flag = 1;
			break;
		}
		else if (n > arr[m])
			j = m - 1;
		else
			i = m + 1;
	}

	if (flag)
		printf("%d exits, %d\n", n, m + 1) ;
	else
		printf("%d doesn't exixt\n", n);
	
	for(i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
