#include <stdio.h>

int main(void)
{
	int i, j;
	/* 上三角 */
	for (i = 0; i < 4; i++){
		for(j = 0; j < 7; j++){
			if (j <= 3 + i && j >= 3 - i)
				putchar('*');
			else
				putchar(' ');
		}
		putchar('\n');
	}

	/* 下三角 */
	for (i = 2; i >= 0; i--){
		for( j = 0; j < 7; j++){
			if( j >=3 -i && j<= 3 + i)
				putchar('*');
			else
				putchar(' ');
		}
		putchar('\n');
	}
	
	return 0;
}

