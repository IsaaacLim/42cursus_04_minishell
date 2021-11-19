#ifndef PARSER_H
#define PARSER_H

#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_comm
{
    char **str;
    int pipe;
} t_comm;


typedef enum
{
    none,
    in,
    in_heredoc,
    out,
    out_append
} e_redirection;

// Struct for simple command
typedef struct s_cmd
{
    char **args;
    int input;
    int output;
    char *infile;
    char *outfile;
} t_cmd;

// NULL terminated s_commands
typedef struct s_commands
{
    t_cmd *commands;
    int len;
    // in/out/>>/<<
} t_commands;

#endif