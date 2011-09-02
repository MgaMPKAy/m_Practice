#include <stdio.h>
#include <string.h>
int main(void)
{
	char en[80] = {0};
	int i;
	
	printf("Input: ");
	fgets(en, 80, stdin);
	
	for (i = 0; i < strlen(en) - 1; i++){
		if (en[i] <= 'Z')
			printf("%c", 'A' + 26 - (en[i] - 'A' +1));
		else
			printf("%c", 'a' + 26 - (en[i] - 'a' + 1));
	}
	return 0;
}
