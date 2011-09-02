#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char cmd[80];
	sprintf(cmd, "rm %s", argv[0]);
	system(cmd);
	return 0;
}
