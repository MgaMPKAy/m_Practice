#include <stdio.h>
#include <tuple>

int main()
{
	auto account = [] () {
		int balance = 0;
		printf("Initial balance: %d\n", balance);
		
		auto set = [&] (int n) {
			printf("Changing balance from %d to %d.\n", balance, n);
			balance = n;
		};
		
		auto get = [&] () {
			return balance;
		};
		
		return std::make_tuple(set,get);
	}();

	printf("Balance: %d\n", std::get<1>(account)());
	printf("Set balance to 5.\n");
	std::get<0>(account)(5);
	printf("Balance: %d\n", std::get<1>(account)());
	
	return 0;
}
