#include <stdio.h>

int main(void)
{
	int m, w, c;
	
	for (m = 1; m <= 36 / 4 ; m++){
		for (w = 1; w <= 36 / 3; w++){
			for (c = 0; c <= 72; c += 2){
				if (m + w + c == 36
				    && m * 4 + w * 3 + c / 2 == 36)
					printf("M:%d, W:%d, C:%d\n",
					       m , w , c);
			}
		}
	}	
	return 0;
}
				    
