#include <stdio.h>
/*都不知到答案那个有什么用 */
void itoa(int num, char *str)
{
    int n = num, w = 1;
    if (num < 10){
	*str = n + '0';
	*(str + 1) = '\0';
    }
    else {
	while (n >= 10){
	    n /= 10;
	    w *= 10;;
	}
	*str = n + '0';

	itoa( num - n * w, str + 1);
    }
}

int main(void)
{
    int n;
    char str[16];
    printf("Enter a int: ");
    scanf("%d", &n);
    
    itoa(n, str);
    printf("%s\n", str);

    return 0;
}
	
