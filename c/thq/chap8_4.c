#include <stdio.h>

void revsers_print(char *str)
{
	if (*str != 0)
		revsers_print(str + 1);
	printf("%c", *str);
}

int main(void)
{
	char str[80];
	
	printf("A string: ");
	scanf("%s", str);
	
	printf("Reversed: ");
	revsers_print(str);
	
	printf("\n");
	return 0;
}
