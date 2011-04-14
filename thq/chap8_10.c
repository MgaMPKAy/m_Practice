#include <stdio.h>
#include <string.h>

long my_atoi(long acc ,char *str)
{
	if (*str == 0) {
		return acc;
	} else {
		return my_atoi(acc * 10 + *str - '0', str + 1);
	}
}

int main(void)
{
	long a, i;
	char str[20];

	printf("A Number String(str): ");
	scanf("%s", str);

	a = my_atoi(0, str);

	printf("A INT(a): %ld\n", a);

	return 0;
}
