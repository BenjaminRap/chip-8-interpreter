#ifndef ARGUMENTS_H
# define ARGUMENTS_H

# include <stdbool.h>

# define FLAG_COUNT 2

typedef enum chip_extension_e {
	CHIP_EXTENSION_NONE,
	EXTENSION_CHIP_48,
	EXTENSION_SUPER_CHIP
}	chip_extension_t;

typedef struct arguments_s {
	char*				program_file;
	chip_extension_t	extension;
}	arguments_t;

bool	read_arguments(int argc, char **argv, arguments_t* arguments);

#endif // !ARGUMENTS_H
