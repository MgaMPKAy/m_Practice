#include <stdio.h>
#define N 4000000

int main(void)
{
    long sum = 0, f1 = 1, f2 = 1, t;
    while (f1 < N){
	t = f2;
	f2 += f1;
	f1 = t;
	if (f2 % 2 == 0)
	    sum += f2;
    }
    printf("%ld\n", sum);
    return 0;
}
