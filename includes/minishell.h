#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parser.h"
# include "environment.h"

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

# define RST  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define BOLD "\x1B[1m"
# define UNDL "\x1B[4m"

typedef struct s_process
{
	char	*input;
	t_list	*env;
}	t_process;

struct s_exstat
{
	int		exit_status;
	t_envar	*env;
}	;

struct s_exstat	g_exstat;

//error.c
void	ft_libft_error(char *message);
void	ft_perror_exit(char *message);

// execute_utils.c
char	**ft_get_envp(t_list *env);
void	ft_dup2(int oldfd, int newfd);
char	**split_path(t_list *env);

//ft_execute.c
void	ft_execute(t_commands cmds, t_list *env);

//redirection.c
void	ft_redir_in(t_cmd commands, int *fdin);
void	ft_redir_out(t_cmd commands, int *fdout, int stdout);
void	ft_redir_pipe(int fdnew[2], int fdpipe[2]);

// parser.c
int	read_str(char *str, t_commands **commands, t_list **env);
void	free_commands(t_commands *commands);

// process_init.c
void	ft_process(t_commands *cmds, t_process init);
bool	ft_is_process(t_commands cmds);

//utils.c
void	ft_free_double_arr(char **arr);
void	ft_exit_status(int exit_num);

// process functions
int		ft_cd(char **argv, t_list *env);
void	ft_exit(t_process *init);
void	ft_eval_exit(t_process init, t_commands *cmds);

//signals.c
void	ft_sig_handler(int signo);
void	ft_sig_ignore_eof(bool ignore);

#endif
