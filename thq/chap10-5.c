#include <stdio.h>

long fun(long acc, char *str)
{
	static int sign = 1;
	if (*str == '-') {
		sign = -1;
		str++;
	}
	
	if (*str == '\0') {
		return acc * sign;
	} else {
		return fun(acc * 10 + *str - '0', str + 1);
	}
}

int main(void)
{
	char *str = "-123456";
	long num;
	
	num = fun(0, str);
	printf("%ld\n", num);
	
	return 0;
}
