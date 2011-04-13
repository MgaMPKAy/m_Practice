#include <stdio.h>
#include <string.h>

void  modify(char *str)
{
	int i, t, min = 0;
	int len = strlen(str);
	
	for (i = 0, min = 0; i < len; i++)
		if (str[min] >= str[i])
			min = i;
	if (min == 0)
		return;
	
	t = str[min];
	while (min > 0) {
		str[min] = str[min - 1];
		min--;
	}
	str[0] = t;
	
	//modify(str + 1);
}

int main(void)
{
	char str[80];
	
	printf("A String:  ");
	scanf("%s", str);
	modify(str);
	printf("Modifies: %s\n", str);
	
	return 0;
}
