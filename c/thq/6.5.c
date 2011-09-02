#include <stdio.h>

int main(void)
{
        double sum = 0, i = 0;
	
	for(i = 1; i <= 100; i++){
		sum += i;
	}
	for(i = 1; i <= 50; i++){
		sum+= i * i;
	}
	for(i = 1; i <= 10; i++){
		sum += 1/i;
	}

	printf("sum = %f\n", sum);
	return 0;
}
			    
