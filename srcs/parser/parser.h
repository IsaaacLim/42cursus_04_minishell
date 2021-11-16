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
} t_comm;

// Struct for simple command
typedef struct s_cmd
{
    char **args;
    int len;
} t_cmd;

// NULL terminated s_commands
typedef struct s_commands
{
    t_cmd **commands;
    int len;
    // in/out/>>/<<
} t_commands;

#endif