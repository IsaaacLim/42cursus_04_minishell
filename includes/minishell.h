#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"
#include "parser.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_process
{
	char	*input;
	char	**processes;
	t_list	*env;
}	t_process;

typedef struct	s_input
{
	char	**double_arr;
	bool	has_greater_than;
	bool	has_less_than;
	bool	has_append;
} t_input;

typedef struct	s_subprocess
{
	pid_t pid;
	int fd_to_child;
	int fd_from_child;
} t_subprocess;

//error.c
void	ft_error(char *message);
void	ft_perror(char *message);


//fork.c
void	ft_fork(t_cmd commands, t_subprocess *p, bool first_command, bool last_command);
void	ft_execute3(t_commands *cmds); //temporary

// parser.c
void	read_str(char *str, t_commands **commands);
void free_commands(t_commands *commands);
void print_commands(t_commands *cmds); //temp

// process_init.c
char	**arr_process(void);
void	ft_process(t_process init);
bool	ft_is_process(char *input, char **processes);

//utils.c
void	ft_free_double_arr(char **arr);

// process functions
int		ft_cd(char **argv);
void	ft_exit(t_process *init);

#endif
