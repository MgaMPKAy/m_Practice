#include <stdio.h>

int main(void)
{
	float n = 1, c[4] = {6, 8, 10, 12};
	int i, j;
	
	for (i = 0; i < 4; i++){
		for (j = 0, n = 1; n < 2; j++){
			n *= (1 + c[i]/100);
		}
		printf("When c = %2.0f%%, needs %d years\n", c[i], j);
	}
	return 0;
}
