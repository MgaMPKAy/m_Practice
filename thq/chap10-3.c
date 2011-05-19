#include <stdio.h>

char * match(char *str, char c)
{
	int i;
	for (i = 0; str[i] != c && str[i] != '\n'; i++);
	if (str[i] == '\n')
		return NULL;
	else
		return str + i;
}

int main(void)
{
	char str[80];
	char c;
	char *p;
	
	scanf("%s", str);
	while((c = getchar()) != '\n' && c != EOF);
	scanf("%c", &c);
	p = match(str, c);
	printf("postion = %p\n", p);
	
	return 0;
}
