#include <stdio.h>

void poem(char *p[])
{
	int i;
	for (i = 0; i < 4; i++)
		printf("%c", *(p+i)[0]);
	printf("\n");
}

int main(void)
{
	char *p[4] = {
		"lbcdefg",
		"oijeklm",
		"vperts",
		"evertadada"
	};
	
	poem(p);
	
	return 0;
}
