#include <stdio.h>
  
int main()
{
	int balance = 6;
	printf("balance: %d\n", balance);
          
	auto v = [&] () {
		printf("balance: %d\n", balance);
		balance = 2;
	};
	v();
	v();
	balance = 8;
	v();
  
	return 0;
}
