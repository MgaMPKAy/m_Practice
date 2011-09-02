#include <stdio.h>

void fun(char *str)
{
	int i, j;
	char t;
	//0 1 2 3 4 5 6 \n
	for(i = 1; i <= 5; i++)
		for(j = 5; j > 1; j--)
			if (str[j-1] > str[j]){
				t = str[j-1];
				str[j-1] = str[j];
				str[j] = t;
			}
}

int main(void)
{
	char str[] = "azyxfsb";
	
	printf("%s\n", str);
	fun(str);
	printf("%s\n", str);

	return 0;
}
