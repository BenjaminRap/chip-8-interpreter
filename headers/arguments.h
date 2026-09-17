#ifndef ARGUMENTS_H
# define ARGUMENTS_H

# include <stdbool.h>

typedef struct arguments_s {
	char	*program_file;
	bool	super_chip;
}	arguments_t;

bool	read_arguments(int argc, char **argv, arguments_t* arguments);

#endif // !ARGUMENTS_H
