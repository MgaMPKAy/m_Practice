/* 判断任意整数是否是回文*/
#include <stdio.h>
#include <string.h>
#define N 1000

/* 判断回文 */
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
	char str[80];

	printf("Enter a num: ");
	scanf("%s", str);
	if (is_palindrome(str))
		printf("%s is a palindrome\n", str);
	else
		printf("%s isn't a palindrome\n", str);

	return 0;
}
