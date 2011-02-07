/* 只能复制文本文件 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	FILE *fd[2];
	char buf[1024];

	if (argc != 3){
		printf("Usage: copy filename1 filename2\n");
		exit(EXIT_FAILURE);
	}
	
	fd[0] = fopen(argv[1], "r");
	fd[1] = fopen(argv[2], "w");
	
	if (fd[0] == NULL || fd[1] == NULL){
		printf("File open error\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(buf, sizeof(buf), fd[0]))
		fputs(buf, fd[1]);

	fclose(fd[0]);
	fclose(fd[1]);
	return 0;
}
