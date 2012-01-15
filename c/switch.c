#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	while (1) {
		switch (i) {
		default:
			printf("%s\n","default");
			break;
		case 0:
			while (1) {
				printf("%s\n","0");
				break;
			}
			break;
		case 1:
			printf("%s\n","1");
			break;
		}
	}
	return 0;
}
