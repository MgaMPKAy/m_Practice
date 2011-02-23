#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char *argv[])
{
	long n;
	int name_len;
	FILE *fd;
	char output[80];
	char name[20];
	
	if (argc >= 2) {
		n = atoi(argv[1]);
		printf("%ld\n", n);
	} else {
		printf("Error\n");
		exit(1);
	}
	fd = fopen("./data", "w");
	srand((unsigned long)time(NULL));
	for (; n > 0; n--) {
		name_len = rand() % 19 + 1;
		name[name_len--] = '\0';
		for (; name_len >= 0; name_len--) {
			name[name_len] = 65 + rand() % 26;
		}
		sprintf(output, "%ld %d %d %d %s\n",
			3110010000 - n, 1 + rand() % 100, 1 + rand() % 100, 1 + rand() % 100,
			name);
		fputs(output, fd);
	}
	fclose(fd);
	return 0;
}
