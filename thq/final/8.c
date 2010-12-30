#include <stdio.h>

int main(void)
{
	int r, w, b, s;
	for (r = 1, s = 0; r <= 3; r++){
		for (w = 0; w <= 3; w++){
			for (b = 0; b <= 6; b++){
				printf("Red : %d, White : %d, Black : %d\n",
				       r, w, b);
				s++;
			}
		}
	}
	printf("Total %d\n", s);
	return 0;
}
