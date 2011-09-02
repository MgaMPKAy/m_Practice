#include <stdio.h>
#include <string.h>

char *fun(char *str)
{
	int i, j;
	char t;
	
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--){
		t = str[i];
		str[i] = str[j];
		str[j] = t;
	}
	return str;
}

int main(void)
{
	char str[] = "123456abc";

	printf("%s\n", fun(str));

	return 0;
}
