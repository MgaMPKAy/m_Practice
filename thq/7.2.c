#include <stdio.h>
#define N 10
int main(void)
{
	int a[10];
	int i, j, max, tmp;

	printf("Enter 10 num: ");
	for (i = 0; i < N; i++)
		scanf("%d", a + i);

	for (i = 0; i < N; i++){
		 max = i;
		for (j = i + 1; j < N; j++){
			if (a[j] > a[max]){
				max = j;
			}
		}
		tmp = a[i];
		a[i] = a[max];
		a[max] = tmp;
	}

	for(i = 0; i < N; i++){
		printf("%d ", a[i]);
	}
	return 0;
}
