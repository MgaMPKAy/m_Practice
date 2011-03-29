#include <stdio.h>
#include <string.h>

void itoa_r(long num, char *str)
{
	int n = num, w = 1;
	if (num < 0) {
		str[0] = '-';
		itoa_r(num * -1, str + 1);
		return;
	}
	if (num < 10){
		*str = n + '0';
		*(str + 1) = '\0';
	} else {
		while (n >= 10){
			n /= 10;
			w *= 10;;
		}
		*str = n + '0';
		
		itoa_r( num - n * w, str + 1);
	}
}

int main(void)
{
	long a, i;
	char str[20];

	printf("A Int: ");
	scanf("%ld", &a);

	itoa_r(a, str);

	printf("A string: ");
	for (i = 0; i < strlen(str); i++)
		printf("%c ", str[i]);
	printf("\n");
	return 0;
}
