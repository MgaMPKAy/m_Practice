#include <stdio.h>

int main(void)
{
	long num, div, tmp;
	int wei = 1, i;
	int arr[20] = {0};
	
	printf("Enter a int: ");
	scanf("%ld", &num);

	
	for (tmp = num; ;tmp /= 10 ){
		printf("第%d位是%ld\n", wei, tmp % 10);
		arr[wei-1] = tmp % 10;
		if (tmp < 10) break;
		++wei;
	}
	printf("共%d位\n", wei);
	
	/* check wei > 20 */
	
	printf("逆序:");
	for (i = 0; i < wei; i++){
		printf("%d", arr[i]);
	}
	printf("\n");
		
	return 0;
}
