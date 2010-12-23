#include <stdio.h>
#include <string.h>

int main(void)
{
    long n;
    int i, j, t, s;
    char str[80] = {0};
    
    printf("Enter a int: ");
    scanf("%ld", &n);
    
    if ((s = n) < 0)
	n = -n;
    i = 0;
    do {
	str[i++] = n % 10 + '0';
    } while((n /= 10) > 0);
    if (s < 0)
	str[i++] = '-';
    str[i] = '\0';
    
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--){
	t = str[i];
	str[i] = str[j];
	str[j] = t;
    }
    printf("str:%s\n", str);
    return 0;
}
