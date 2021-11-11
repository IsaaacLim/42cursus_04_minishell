#ifndef PARSER_H
#define PARSER_H

#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_comm
{
	char **str;
	int pipe;
}		t_comm;

// Struct for simple command
typedef struct s_simple
{
	char **args;
	int	len;
}	t_simple;

typedef struct s_command
{
	t_simple **commands;
	int	len;
	// in/out/>>/<<
}		t_command;

#endif