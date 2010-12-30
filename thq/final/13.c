#include <stdio.h>

int main(void)
{
	int a[8] = {10, 2, 3, 4, 5, 6, 7, 8};
	int b[5] = {6, 7, 8, 9, 10};
	int c[8] = {0};
	int i, j, k, tmp, flag;
	for(i = k = 0; i < 8; i++){
		tmp = a[i];
		for (j =  0, flag = 1; j < 5; j++){
			if (b[j] == tmp){
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			c[k++] = tmp;
	}
	
	for (i = 0; c[i] != 0 && i < 8; i++)
		printf("%d ", c[i]);
	printf("\n");
	return 0;
}
