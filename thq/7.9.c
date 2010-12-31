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

	if ( n > arr[0] || n < arr[N-1]){
		printf("Doesn't exist\n");
		return 0;
	}
	for (i = 0, j = N; j - i >= 1; ){
		m = (i + j) / 2;
		if (n == arr[m]){
			flag = 1;
			break;
		}
		else if (n > arr[m])
			j = m;
		else 
			i = m;
	}

	if (flag)
		printf("%d exits, %d\n", n, m + 1) ;
	else
		printf("%d doesn't exixt\n", n);
	return 0;
}
