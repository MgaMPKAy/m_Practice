#include <stdio.h>

int main(void)
{
	float s = 2, d = 1, sum = 0, t;
	int i;
	
	for (i = 1; i <= 20; i++){
		sum += s / d;
		t = s;
	s = d + s;
	d = t;
    }
	
	printf("%f\n", sum);
	return 0;
}
