#include <stdio.h>

int main(void)
{
	float n = 1, c;
	int i;

	for (i = 0, c = 6, n = 1; n < 2; i++){
		n *= (1 + c / 100);
	}
	printf("When c = %2.0f%%, needs %d years\n", c, i);

	for (i = 0, c = 8, n = 1; n < 2; i++){
		n *= (1 + c / 100);
	}
	printf("When c = %2.0f%%, needs %d years\n", c, i);

	for (i = 0, c = 10, n = 1; n < 2; i++){
		n *= (1 + c / 100);
	}
	printf("When c = %2.0f%%, needs %d years\n", c, i);

	for (i = 0, c = 12, n = 1; n < 2; i++){
		n *= (1 + c / 100);
	}
	printf("When c = %2.0f%%, needs %d years\n", c, i);
	
	return 0;
}
