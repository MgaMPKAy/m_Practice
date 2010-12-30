#include <stdio.h>

int main(void)
{
	int m, w, c;
	
	for (m = 0; m <= 100 / 3 ; m++){
		for (w = 0; w <= 100 / 2; w++){
			for (c = 0; c <= 100 * 2; c += 2){
				if (m + w + c == 100
				    && m * 3 + w * 2 + c / 2 == 100)
					printf("M:%d, W:%d, C:%d\n",
					       m , w , c);
			}
		}
	}	
	return 0;
}
				    
