/* 判断任意整数是否是回文*/
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[80];
	int i, j, flag = 0;
	printf("Enter a num: ");
	scanf("%s", str);
	
	for(i = 0, j = strlen(str) - 1; i < j; i++, j--){
		if (str[i] != str[j]){
			printf("%s isn't a palindrome\n", str);
			return 0;
		}
	}
	printf("%s is a palindrome\n", str);
	return 0;
}
