#include <stdio.h>
#include <string.h>

int main(void)
{
    long num;
    int i, j,t;
    char str[80] = {0};
    
    printf("Enter a int: ");
    scanf("%ld", &num);

    for (i = 0; ;){
	str[i++] = num % 10 + '0';
	if (num < 10) break;
	else num = (num - num % 10) / 10;
    }
    str[i] = '\0';
    
    for (i = 0, j = strlen(str) - 1; i < strlen(str) / 2; i++, j--){
	t = str[i];
	str[i] = str[j];
	str[j] = t;
    }
    printf("str:%s\n", str);
    return 0;
}
