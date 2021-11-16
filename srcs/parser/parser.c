#include "parser.h"

// Copied from Isaac's readline.c
void ft_free_double_arr(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
		i++;
	printf("free: %d\n", i);
	while (--i >= 0)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
	return;
}

int num_pipes(char **str_arr)
{
	int pipes;

	pipes = 0;
	while (*str_arr)
	{
		if (ft_strncmp(*str_arr, "|", 1) == 0)
			pipes++;
		str_arr++;
	}
	return (pipes);
}

// TODO - free commands
// TODO - process error

/*
	This somehow works
	- cat -n < what
	- cat < what -n

*/

/*
	4 Scenarios
	- << & char *
	- < & char *
	- > & char *
	- >> & char *

	Check against str_arr + 1 incase its null terminated

	returns redirection enum,
	0 would mean a redirection is not found
*/
int is_redirection(char *str, t_cmd *cmd, char *next)
{
	int redir;

	redir = 0;
	if (ft_strncmp(str, "<", 1) == 0)
		redir = in;
	else if (ft_strncmp(str, "<<", 2) == 0)
		redir = in_heredoc;
	else if (ft_strncmp(str, ">", 1) == 0)
		redir = out;
	else if (ft_strncmp(str, ">>", 2) == 0)
		redir = out_append;
	if (cmd)
	{
		if (redir == in || redir == in_heredoc)
		{
			cmd->input = redir;
			cmd->infile = ft_strcpy(next);
		}
		else if (redir == out || redir == out_append)
		{
			cmd->output = redir;
			cmd->outfile = ft_strcpy(next);
		}
	}
	return (redir);
}

bool valid_redirection(char **str_arr)
{
	while (*str_arr)
	{
		if (is_redirection(*str_arr, NULL, NULL))
		{
			if (*(str_arr + 1) == NULL || ft_strncmp(*(str_arr + 1), "|", 1) == 0)
				return (false);
		}
		str_arr++;
	}
	return (true);
}

bool valid_pipe(char **str_arr)
{
	int i;

	i = 0;
	while (str_arr[i])
	{
		// return false if pipe is first arg
		if (i == 0 && ft_strncmp(str_arr[i], "|", 1) == 0)
			return (false);
		if (ft_strncmp(str_arr[i], "|", 1) == 0)
		{
			// checks if previous/next arg is pipe, and if next is NULL
			if (str_arr[i + 1] == NULL || ft_strncmp(str_arr[i - 1], "|", 1) == 0 || ft_strncmp(str_arr[i + 1], "|", 1) == 0)
				return (false);
		}
		i++;
	}
	return (true);
}

/*
	Edge cases for handling redirection
	- no other commands (works)
		- < filename.txt
		- > filename.txt - creates empty file
	Sequence doesn't matter
		- > hi cat < README.md
	Prompts syntax error if missing filename
		- > [missing filename]
		- [missing filename] <
	
	Return NULL if syntax error found
*/
t_cmd parse_singlecmd(char **str_arr)
{
	int i;
	int arg_len;
	int redir;
	t_cmd cmd;

	i = 0;
	arg_len = 0;
	redir = 0;
	// checks that str_arr is not null terminated
	while (str_arr[i] && ft_strncmp(str_arr[i], "|", 1) != 0)
	{
		if (is_redirection(str_arr[i], &cmd, str_arr[i + 1]))
			arg_len++;
		i++;
	}
	/* 
		- arg_len calculated above stores the number of redirections
		- I'm assuming that our function below would have cleaned and made sure that every redirection
			is paired with a corresponding filename
	*/
	arg_len = i - (2 * arg_len);
	cmd.args = malloc(sizeof(char *) * arg_len + 1);
	i = 0;
	while (str_arr[i] && ft_strncmp(str_arr[i], "|", 1) != 0)
	{
		if (is_redirection(str_arr[i], NULL, NULL))
			i += 2;
		else
			i++;
	}
	(cmd.args)[arg_len] = NULL;
	return (cmd);
}

/*
	// NO LONGER NEED NULL TERMINATOR
	Assumes str is a single string of commands
	- Passing in argument with no pipe, will malloc t_cmd ** of 2
		a. first t_cmd * for first command
		b. 2nd t_cmd for NULL terminate
		c. This assumes that the first command will have a command
	- Passing in arg with 1 pipe and above
		a. will malloc t_cmd ** of 1 pipe + 2 (1 for a command and another for NULL)
*/

// Do i even need to return a pointer for this?
t_commands *parse_commands(char *str)
{
	char **str_arr;
	t_commands *commands;
	int cmd_len;

	str_arr = ft_split(str, ' ');
	cmd_len = num_pipes(str_arr) + 1;
	if (!valid_redirection(str_arr) || !valid_pipe(str_arr))
	{
		printf("Syntax error near unexpected token");
		ft_free_double_arr(str_arr);
		return (NULL);
	}
	commands = malloc(sizeof(t_commands));
	commands->commands = malloc(sizeof(t_cmd) * cmd_len + 1);
	commands->len = cmd_len;
	// Parse commands
	ft_free_double_arr(str_arr);
}

int main(int argc, char *argv[])
{
	return (0);
}