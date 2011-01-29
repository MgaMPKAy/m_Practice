#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd;
	unsigned long rtc = 0;
	fd = open("/dev/rtc", O_RDONLY);
	if (fd == -1)
		exit(-1);
	read(fd, &rtc, sizeof(rtc));
	printf("rtc = %ld\n", rtc);
	return 0;
}
	
	
