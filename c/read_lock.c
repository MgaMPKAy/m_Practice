#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int lock_set(int fd, int type);

int main(void)
{
	int fd;

	fd = open("./data", O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		printf("Open file error\n");
		exit(EXIT_FAILURE);
	}

	lock_set(fd, F_RDLCK);
	getchar();
	lock_set(fd, F_UNLCK);
	getchar();

	close(fd);
	return 0;
}
