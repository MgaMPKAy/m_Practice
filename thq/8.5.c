#include <stdio.h>
#include <string.h>

char *reverse(char *str)
{
    int i, j, s;
    char t;
    s = strlen(str);

    for (i = 0, j = s - 1; i < s / 2; i++, j--){
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
