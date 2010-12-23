#include <stdio.h>
#include <string.h>

char *reverse(char *str)
{
    int i, j;
    char t;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--){
	t = str[i];
	str[i] = str[j];
	str[j] = t;
    }
    return str;
}

int main(void)
{
    char str[80];
    
    printf("Enter a string:");
    fgets(str, 80, stdin);
    str[strlen(str) - 1] = '\0';
    //scanf("%s",str);
    
    printf("%s\n", reverse(str));
    return 0;
}
