#include <stdio.h>

void fun(char *tt, int pp[])
{
	while (*tt != '\0') {
		if (*tt >= 'a' && *tt <= 'z') {
			pp[*tt - 'a']++;
		}
		tt++;
	}
}

int main(void)
{
	char str[] = "AaaBbCcEFoxqlZzx";
	int p[26] = {0}, i;

	printf("%s\n", str);
	fun(str, p);

	for (i = 0; i < 26; i++) {
		printf("%c %d\n", 'a' + i, p[i]);
	}
	
	return 0;
}
 
