#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd_src, fd_dest, len;
	char buf[1024];
	char usage[] = "Usage: copy filename1 filename2\n";
	if (argc != 3){
		write(STDOUT_FILENO, usage, sizeof(usage));
		exit(EXIT_FAILURE);
	}
	
	fd_src = open(argv[1], O_RDONLY);
	fd_dest = open(argv[2], O_WRONLY | O_CREAT |O_TRUNC, 0644);
	
	if (fd_src < 0 || fd_dest < 0) {
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	
	while ((len = read(fd_src, buf, sizeof(buf))) >  0) {
		write(fd_dest, buf, len);
	}
	
	close(fd_src);
	close(fd_dest);
	return 0;
}
	
