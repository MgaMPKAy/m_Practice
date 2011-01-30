#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd, num;
	fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != -1){
		read(fd, &num, sizeof(int));
		printf("The globalvar is %d\n", num);
		
		printf("Please enter the num to write to globalvar:> ");
		scanf("%d", &num);
		write(fd, &num, sizeof(int));
		
		read(fd, &num, sizeof(int));
		printf("The globalvar is %d\n", num);
		
		close(fd);
	} else {
		printf("Device open failure\n");
	}
	return 0;
}
