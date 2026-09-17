#include <stdio.h>
#include <string.h>

#include "arguments.h"

arguments_t	read_arguments(int argc, char **argv) {
	arguments_t	arguments;

	bzero(&arguments, sizeof(arguments));
	for (int i = 1; i < argc; i++) {
		char	*arg = argv[i];

		if (!strcmp(arg, "--super-chip"))
			arguments.super_chip = true;
		else if (!arguments.program)
			arguments.program = arg;
		else {
			fprintf(stderr, "Invalid argument : %s", arg);
			arguments.valid = false;
			break ;
		}
	}
	return arguments;
}
