#include <stdio.h>
#include <string.h>

#include "arguments.h"

bool	read_arguments(int argc, char **argv, arguments_t* arguments) {
	bool	is_valid = false;

	bzero(arguments, sizeof(arguments_t));
	for (int i = 1; i < argc; i++) {
		char	*arg = argv[i];

		if (!strcmp(arg, "--super-chip"))
			arguments->super_chip = true;
		else if (!arguments->program_file) {
			arguments->program_file = arg;
			is_valid = true;
		}
		else {
			fprintf(stderr, "Invalid argument : %s\n", arg);
			is_valid = false;
			break ;
		}
	}
	if (!arguments->program_file)
		fprintf(stderr, "Missing program_file\n");
	if (is_valid)
		fprintf(stderr, "Usage : %s <program_file> [--super-chip]\n", argv[0]);
	return is_valid;
}
