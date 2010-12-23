#include <stdio.h>

int main(void)
{
    long  sum = 0, tmp;
    int a, n, i, j;
    
    printf("Enter a n: ");
    scanf("%d %d", &a, &n);
    
    for (i = 1; i <= n; i++){
	for (tmp = a,j = 1; j < i; j++){
	    tmp = tmp * 10 + a;
	}
	sum += tmp;
    }
    
    printf("sum = %ld\n", sum);
    return 0;
}
