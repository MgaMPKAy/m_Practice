#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *path = argv[1];
	int ret;

	ret = access(path, F_OK);
	if (ret == 0)
		printf("%s exists\n", path);
	else {
		if (errno == ENOENT)
			printf("%s doesn't exist\n", path);
		else if (errno == EACCES)
			printf("%d is not accessible\n", path);
		return 0;
	}

	ret = access(path, R_OK);
	if (ret == 0)
		printf("%s is readable\n", path);
	else
		printf("%s is  not readable(access denied)\n", path);

	ret = access(path, W_OK);
	if (ret == 0)
		printf("%s is writable\n", path);
	else if (errno == EACCES)
		printf("%s is not writable(access denied)\n", path);
	else if (errno == EROFS)
		printf("%s is not writable(read-only filesystem)\n", path);
	return 0;
}
