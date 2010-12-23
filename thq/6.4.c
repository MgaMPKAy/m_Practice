#include <stdio.h>
#define N 20
int main(void)
{
        long fac, sum = 0;
	int i, j;
	
	for(i = fac = 1; i <= N; i++){
		for(j = 1; j <= i; j++){
			fac = j * fac;
		}
		sum += fac;
		fac = 1;
	}

	printf("sum = %ld\n", sum);
}
			    
