#ifndef ARGUMENTS_H
# define ARGUMENTS_H

# include <stdbool.h>

typedef struct arguments_s {
	char	*program;
	bool	super_chip;
	bool	valid;
}	arguments_t;

arguments_t	read_arguments(int argc, char **argv);

#endif // !ARGUMENTS_H
