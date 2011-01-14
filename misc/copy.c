#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fd[2];
	int c;
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
	
	while ((c = fgetc(fd[0])) != EOF)
		fputc(c, fd[1]);
	
	fclose(fd[0]);
	fclose(fd[1]);
	return 0;
}
