#include <stdio.h>

int main(void)
{
	int a, b, c, d, e, f;
	int flag = 1;
	
	for (a = 0; a < 2; a++){
		for (b = 0; b < 2; b++){
			for (c = 0; c < 2; c++){
				for (d = 0; d < 2; d++){
					for (e = 0; e < 2; e++){
						for (f = 0; f < 2; f++){
							flag = 1;
							/* 1 */
							if (c == 0 && b ==0)
								flag = 0;
							/* 2 */
							if ((c == 1 && d== 1)
							    || (c== 0 && d == 0))
								flag = 0;
							/* 3 */
							if (d != e)
								flag = 0;
							/* 4 */
							if (a + b + f != 2)
							    flag = 0;
							/* 5 */
							if (c == 1 && f == 1)
								flag = 0;
							/* 6 */
							if ((e == 0 && f == 0)
							    || (e == 1 && f == 1))
								flag = 0;

							if (flag == 1){
								printf("%d %d %d %d %d %d\n",
								       a, b, c, d, e, f);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
								
							 
