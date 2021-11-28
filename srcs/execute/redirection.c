#include "minishell.h"
#include "get_next_line.h"

#include <termios.h>

/*
** display value of EOF character with term1.c_cc[VEOF]
*/
static void	ft_sig_ignore_EOF(bool ignore)
{
	struct termios term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		perror("tcgetattr error");
	else
	{
		if (ignore)
			term1.c_cc[VEOF] = 0;
		else
			term1.c_cc[VEOF] = 04;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
			perror("tcsetattr() error");
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
			perror("tcgetattr() error");
	}
}

/*
** HEREDOC
** Read input (get_next_line) from STDIN
** Write gnl output to pipe_out_fd
** Replace pipe_in_fd to be dup2 with STDIN
*/
static void	ft_heredoc(char *infile, int *fdin)
{
	char	*line;
	int		ret;
	int		fdtemp[2];

	ft_sig_ignore_EOF(true);
	signal(SIGINT, SIG_IGN);
	pipe(fdtemp);
	write(1, "heredoc> ", 9);
	ret = get_next_line(0, &line);
	while (ret > 0)
	{
		if (!ft_strncmp(line, infile, ft_strlen(infile) + 1))
			break ;
		write(1, "heredoc> ", 9);
		write(fdtemp[1], line, ft_strlen(line));
		write(fdtemp[1], "\n", 1);
		free(line);
		ret = get_next_line(0, &line);
	}
	free(line);
	*fdin = fdtemp[0];
	close(fdtemp[1]);
	ft_sig_ignore_EOF(false);
	signal(SIGINT, ft_sig_handler);
}

void	ft_redir_in(t_cmd commands, int *fdin)
{
	if (commands.input == in)
	{
		*fdin = open(commands.infile, O_RDONLY | O_CLOEXEC, 0777);
		if (*fdin < 0)
			perror("infile failed to open");
	}
	else if (commands.input == in_heredoc)
		ft_heredoc(commands.infile, fdin);
	ft_dup2(*fdin, 0);
}

void	ft_redir_out(t_cmd commands, int *fdout, int stdout)
{
	if (commands.output)
	{
		if (commands.output == out)
			*fdout = open(commands.outfile, O_WRONLY | O_TRUNC | O_CREAT
					| O_CLOEXEC, 0777);
		else if (commands.output == out_append)
			*fdout = open(commands.outfile, O_WRONLY | O_APPEND | O_CREAT
					| O_CLOEXEC, 0777);
		if (*fdout < 0)
			perror("outfile failed to open");
	}
	else
		*fdout = dup(stdout);
}

void	ft_redir_pipe(int fdnew[2], int fdpipe[2])
{
	if (pipe(fdpipe) == -1)
		perror("failed to create pipe");
	fdnew[1] = fdpipe[1];
	fdnew[0] = fdpipe[0];
}
