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
# include <sys/signal.h>


typedef struct	s_process
{
	char	*input;
	t_list	*env;
}	t_process;

int	g_exit_status;

//error.c
void	ft_error(char *message);
void	ft_perror(char *message);

// execute_utils.c
char	**ft_get_envp(t_list *env);
void	ft_dup2(int oldfd, int newfd);

//ft_execute.c
void	ft_execute(t_commands cmds, t_list *env);

//redirection.c
void	ft_redir_in(t_cmd commands, int *fdin);
void	ft_redir_out(t_cmd commands, int *fdout, int stdout);
void	ft_redir_pipe(int fdnew[2], int fdpipe[2]);

// parser.c
void	read_str(char *str, t_commands **commands);
void free_commands(t_commands *commands);
void print_commands(t_commands *cmds); //temp

// process_init.c
// char	**arr_process(void);
void	ft_process(t_process init);
bool	ft_is_process(char *input);

//utils.c
void	ft_free_double_arr(char **arr);

// process functions
int		ft_cd(char **argv);
void	ft_exit(t_process *init);
void	ft_eval_exit(t_process init, char **argv);


//signals
void ft_sig_handler();

#endif
