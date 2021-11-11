#include "parser.h"

char *ft_strcpy(char *str)
{
	char *tmp;
	int i;

	i = 0;
	tmp = malloc(sizeof(ft_strlen(str) + 1));
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

t_comm *gen_command(char **commands, int len, int op)
{
	t_comm *com;
	int i;
	
	com = malloc(sizeof(t_comm));
	// +1 to null terminate
	com->str = malloc(sizeof(char *) * (len + 1));
	com->pipe = op;
	i = 0;
	while (i < len)
	{
		(com->str)[i] = ft_strcpy(commands[i]);
		i++;
	}
	(com->str)[len] = NULL;
	return (NULL);
}

int	is_op(char *str)
{
	int i;
    const char *op[5] = {"<", "<<", ">", ">>", "|"};
	
	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(op[i], str, INT_MAX))
			return (i);
	}
	return (-1);
}

bool is_pipe(char *str)
{
	return ((ft_strncmp(str, "|", INT_MAX)) == 0);
}

/*
	pass in pointer oof
*/
t_list  *gen_command_list(char **argv, int len)
{
	int i;
	int com_len;
	char **ptr;
	int op;
	t_list *commands;

	i = 0;
	com_len = 0;
	ptr = argv;
	commands = NULL;
	while (i < len)
	{
		com_len++;
		op = is_pipe(argv[i]);
		if ((op >= 0 && op <= 5) || i == len - 1)
			ft_lstadd_back(&commands, ft_lstnew(gen_command(ptr, com_len, op)));
		if (op >= 0 && op <= 5)
			ptr = ptr + com_len;
		i++;
	}
	return (commands);
}

int main(int argc, char *argv[])
{
	return (0);
}