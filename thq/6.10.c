#include <stdio.h>

int main(void)
{
    int i = 1, sum = 1;
    
    for (i = 1; i <= 9; i++){
	sum = (sum + 1) * 2;
    }

    printf("%d\n", sum);
    return 0;
}
