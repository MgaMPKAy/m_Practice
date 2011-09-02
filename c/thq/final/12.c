#include <stdio.h>
#include <string.h>
#define N 1000

char *itoa(long num, char *str)
{
	long s;
	if ((s = num) < 0)
		num = - num;
	int i = 0;
	do {
		str[i] = num % 10 + '0';
		num /= 10;
		i++;
	} while (num >= 10);
	str[i] = num + '0';
	if (s < 0)
		str[++i] = '-';
	str[++i] = '\0';
	return str;
}

int is_palindrome(char *str)
{
	int i, j;
	for(i = 0, j = strlen(str) - 1; i < j; i++, j--){
		if (str[i] != str[j])
			return 0;
	}
	return 1;
}

int main(void)
{
	long n;;
	char str[32];
	
	printf("Enter a num: ");
	scanf("%ld", &n);
	if (is_palindrome(itoa(n, str)))
		printf("%ld is a palindrome\n", n);
	else
		printf("%ld isn't a palindrome\n", n); 
	
	return 0;
}
