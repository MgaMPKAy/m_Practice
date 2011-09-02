#include <stdio.h>

void split(int n)
{
	int arr[10], i;
	for (i = 0;; n /= 10){
		arr[i++] = n  % 10;
		if (n < 10) break;
	}
	arr[i] = '\0';
	
	for (i = i - 1; i > 0; i--){
		printf("%d  ",arr[i]);
	}
	printf("%d\n", arr[0]); 
}

int main(void)
{
	int n;
	printf("Enter a int:");
	scanf("%d", &n);
	split(n);
	return 0;
}
