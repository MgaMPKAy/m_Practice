#include <stdio.h>

int main(void)
{
    int i = 1;
    long sum = 0;
    for (i = 1; i < 1000; i++){
	if (i % 3 == 0 || i % 5 == 0){
	    sum += i;
	}
    }
    printf("%ld\n", sum);
    return 0;
}
