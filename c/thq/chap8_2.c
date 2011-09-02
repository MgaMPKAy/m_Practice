#include <stdio.h>

int coins[3] = {1, 5, 10};

void count(int money)
{
	int i, j, k, c = 0;
	for (k = money / 10; k >= 0; k--) {
		for (j = money / 5; j >= 0; j--) {
			for (i = money; i >= 0; i--) {
				if (i + 5 * j + 10 * k == money) {
					printf("1*%d, 5*%d, 10*%d\n",
					       i, j, k);
					c++;
				}
			}
		}
	}
	printf("total: %d\n", c);
}

int main(void)
{
	int money;
	printf("How much money do you have?: ");
	scanf("%d", &money);
	count(money);
	return 0;
}
