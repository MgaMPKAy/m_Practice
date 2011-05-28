#include <stdio.h>
#include <tuple>
#include <memory>

void deleter(int* p)
{
	printf("deleting %p\n", p);
	delete p;
}

int main()
{
	auto account = [] () {
		std::shared_ptr<int> balance(new int(0), deleter);
		printf("Initial balance: %d (%p)\n", *balance, balance.get());
		printf("balance.use_count(): %ld\n", balance.use_count());
		auto set = [=] (int n) {
			printf("Changing balance from %d to %d.\n", *balance, n);
			*balance = n;
		};
		auto get = [=] () {
			return *balance;
		};
		printf("balance.use_count(): %ld\n", balance.use_count());
		return std::make_tuple(set,get);
	}();
	printf("Balance: %d\n", std::get<1>(account)());
	printf("Set balance to 5.\n");
	std::get<0>(account)(5);
	printf("Balance: %d\n", std::get<1>(account)());
	return 0;
}
