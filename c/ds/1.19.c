#include <stdio.h>
#include <math.h>

typedef enum {OK, OVERFLOW} Status;

int fact(int n)
{
	int sum = 1;
	int i;
	for (i = 1; i <= n; i++) {
		sum *= i;
	}
	return sum;
}

Status Series(int ARRSIZE, int a[])
{
	Status flag = OK;
	for (int i = 1; i <= ARRSIZE; i++) {
		a[i - 1] = fact(i) * pow(2, i);
		if (a[i - 1] < 0) flag = OVERFLOW;
	}
	return flag;
}

int main(int argc, char *argv[])
{
	int a[13];
	printf("%d\n", Series(5, a));

	for (int i = 0; i < 13; ++i) {
		printf("%d\n", a[i]);
	}

	return 0;
}
