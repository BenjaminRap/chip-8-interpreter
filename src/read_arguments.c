#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arguments.h"

int	compare_strings(const void* a, const void* b) {
	return strcmp(*(const char**)a, *(const char**)b);
}

bool	read_arguments(int argc, char **argv, arguments_t* arguments) {
	const static char* flags[FLAG_COUNT] = {
		"--chip-48",
		"--super-chip",
	}; // Should be in the same order as the enum
	const static int	extension_flags_end = 2;
	bool				is_valid = false;

	bzero(arguments, sizeof(arguments_t));
	for (int i = 1; i < argc; i++) {
		char	*arg = argv[i];

		const char**	result = bsearch(arg, flags, FLAG_COUNT, sizeof(char*), compare_strings);

		if (result != NULL) {
			const int	index = result - flags;

			if (index < extension_flags_end) {
				if (arguments->extension != CHIP_EXTENSION_NONE)
					printf("Warning : Multiples flag extension found, using the latest.");
				arguments->extension = (chip_extension_t)(index + 1);
			}
		}
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
	if (is_valid && !arguments->program_file)
		fprintf(stderr, "Missing program_file\n");
	if (!is_valid)
		fprintf(stderr, "Usage : %s <program_file> [--super-chip] [--chip-48]\n", argv[0]);
	return is_valid;
}
