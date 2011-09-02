#include <stdio.h>

int main(void)
{
	float s = 0, h = 100;
	int i;
	for (i = 0; i < 10; i++, h /= 2){
		s += h + h / 2;
		if (9 == i)
			printf("Tenth :%f\n", h / 2);
	}
	
	printf("Total = %f\n", s);
	return 0;
}
