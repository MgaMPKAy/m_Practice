#include <stdio.h>
#include <math.h>
#define N  600851475143

int isprime(long n)
{
    long sq = (long int)sqrt(n) + 1;
    long i;
    for (i = 2; i < sq; i++){
	if (n % i == 0)
	    return 0;
	else
	    continue;
    }
    return 1;
}

int main(void)
{
    long maxp, i;
    double sq;

    sq = sqrt(N);
    for (i = 2; i < sq; i++){
	if (N % i != 0)
	    continue;
	if (isprime(i))
	    maxp = i;
    }
    printf("%ld\n", maxp);

    return 0;
}
