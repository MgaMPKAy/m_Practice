#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i, j, bits, max;
	max = 1 << (argc - 1);
	for (i = 0; i < max; i++) {
		int f = 1;
		printf("{");
		for (bits = i , j = 0; bits; bits >>= 1, j++) {
			if (bits & 0x1) {
				printf(f ? "%s" : ", %s", argv[j + 1]);
				f = 0;
			}
		}
		printf("}\n");
	}
}
