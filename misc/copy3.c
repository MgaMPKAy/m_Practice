#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd_src, fd_dest;
	struct stat stat_buf;
	off_t offset = 0;
	char usage[] = "Usage: copy filename1 filename2\n";
	
	if (argc != 3){
		write(STDOUT_FILENO, usage, sizeof(usage));
		exit(EXIT_FAILURE);
	}
	
	fd_src = open(argv[1], O_RDONLY);
	fstat(fd_src, &stat_buf);
	fd_dest = open(argv[2], O_WRONLY |O_CREAT, stat_buf.st_mode);
	
	if (fd_src < 0 || fd_dest < 0) {
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	
	sendfile(fd_dest, fd_src, &offset, stat_buf.st_size);

	close(fd_src);
	close(fd_dest);
	return 0;
}
	
