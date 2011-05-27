#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

const char *program_name;

void print_usage(FILE *stream, int exit_code)
{
	fprintf(stream, "Usage :%s options [inputfile ...]\n", program_name);
	fprintf(stream,
		" -h --help              Display help info\n"
		" -o --output filename   Display help info\n"
		" -v --help Display help info\n");
	exit(exit_code);
}

int main(int argc, char *argv[])
{
	int next_option;
	
	const struct option long_options[] = {
	{"help", 0, NULL, 'h'},
	{"output", 1, NULL, 'o'},
	{"verbose", 0, NULL, 'v'},
	{NULL, 0, NULL, 0},
	};
	
	const char *output_filename = NULL;
	int verbose = 0;
	program_name = argv[0];
	
	do {
		switch (next_option) {
		case 'h':
			print_usage(stdout, 0);
		case 'o':
			output_filename = optarg;
			break;
		case 'v' :
			verbose = 1;
			break;
		case '?':
			print_usage(stderr, 1);
		case -1:
			break;
		default:
			abort();
		}
	} while (next_option != -1);

	if (verbose) {
		int i;
		for (i = optind; i < argc; ++i)
			printf("Argument: %s\n", argv[i]);
	}
	
	return 0;
}
