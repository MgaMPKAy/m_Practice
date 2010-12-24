#include <stdio.h>

int mystrlen(char *str)
{
    int l;
    for (l = 0; str[l] != '\0'; l++);
    /* do nothing */
    return l;
}

int main(void)
{
    int len;
    char str[80];

    printf("Enter a string:");
    scanf("%s", str);

    len = mystrlen(str);
    printf("Strlen: %d\n", len);

    return 0;
}
