#define func(arg) do { 	     \
			     \
	} while(0)

int main(int argc, char *argv[])
{
	if (1 == 0)
		func(1);
	else
		return 0;
}
