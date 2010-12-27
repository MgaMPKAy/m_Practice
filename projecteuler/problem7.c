#include <stdio.h>
#include <math.h>

int isprime(int num)
{
	long i, sq;
	sq = sqrt(num) + 1;
	for (i = 2; i < sq; i++){
		if (0 == num % i)
			return 0;
	}
	return 1;
}

int main(void)
{
	int s = 0;
	long i;
	for (i = 2; i < 100000000; i++){
		if (isprime(i))
			s++;
		if(s == 10001){
			printf("%ld\n", i);
			break;
		}
	}
	return 0;
}
