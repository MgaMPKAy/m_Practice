#include <stdio.h>

int main(void)
{
	char str[80];
	int n, i;

	scanf("%s", str);
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		printf("%c", str[i]);
	}
	printf("\n");

	return 0;
}
	       
			
	
