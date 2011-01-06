#include <stdio.h>
#define A ((1&i) != 0)
#define B ((2&i) != 0)
#define C ((4&i) != 0)
#define D ((8&i) != 0)
#define E ((16&i) != 0)
#define F ((32&i) != 0)

int main(void)
{
	int i;
	for (i = 0; i < (1<<6); i++){
		if ((!C && B)
		    && ((C != D) && (C || D))
		    && (D == E)
		    && ((A + B + F) == 2)
		    && (!((C || F) && C == F))
		    && ((E || F) && (E != F))){
			if (A) printf("A ");
			if (B) printf("B ");
			if (C) printf("C ");
			if (D) printf("D ");
			if (E) printf("E ");
			if (F) printf("F ");
		}
	}
	printf("\n");
	return 0;
}
