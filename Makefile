NAME		=	minishell

SRCS_DIR	=	./srcs/
SRCS_LST	=	main.c		process.c		utils.c		signals.c	\

EXEC_DIR	=	execute/
EXEC_LST	=	ft_execute.c	execute_utils.c		redirection.c
EXEC		=	$(addprefix $(EXEC_DIR), $(EXEC_LST))

PROCS_DIR	=	processes/
PROCS_LST	=	env_validate.c		environment_utils.c						\
				ft_environment.c	export.c		unset.c					\
				ft_cd.c				ft_exit.c
PROCS		=	$(addprefix $(PROCS_DIR), $(PROCS_LST))

PARSER_DIR	=	parser/
PARSER_LST	=	parser.c			parser_utils.c 		parser_utils2.c		\
				parse_env.c			parse_env_utils.c						\
				ft_split_enhanced.c
PARSER		=	$(addprefix $(PARSER_DIR), $(PARSER_LST))

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST) $(EXEC) $(PROCS) $(PARSER))
OBJS		=	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HDRS_LST	=	minishell.h parser.h environment.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HDRS_LST))

LIBFT_DIR	=	./libft/
LIBFT		=	$(LIBFT_DIR)libft.a
LIBFT_HDRS	=	$(LIBFT_DIR)includes/

INCLUDES	=	-I $(HDRS_DIR) -I $(LIBFT_HDRS)

# RL_LIB		=	-lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
RL_LIB		=	-L/usr/include -lreadline
#gcc test.c -o test -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include
# -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror

BUILT_INS	=	./srcs/built_ins/

all: $(NAME) 
# $(BUILT_INS)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(RL_LIB) -o $@

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)
	make -C $(BUILT_INS) #need to fix this

# $(BUILT_INS) :

clean:
	make clean -C $(BUILT_INS)
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean:	clean
	make fclean -C $(BUILT_INS)
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
