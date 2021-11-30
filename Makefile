NAME		=	minishell

SRCS_DIR	=	./srcs/
PARSER_LST	=	parser/parser.c	parser/parser_utils.c parser/parser_utils2.c	\
				parser/parse_env.c		parser/parse_env_utils.c			\
				parser/ft_split_enhanced.c
SRCS_LST	=	error.c			${PARSER_LST}	main.c		\
				process_init.c	utils.c

EXEC_DIR	=	execute/
EXEC_LST	=	ft_execute.c	execute_utils.c		ft_execute_paths.c	redirection.c
EXEC		=	$(addprefix $(EXEC_DIR), $(EXEC_LST))

PROCS_DIR	=	process/
PROCS_LST	=	env_validate.c		env.c			environment_utils.c		\
				ft_environment.c	export.c		unset.c					\
				ft_cd.c				ft_exit.c
PROCS		=	$(addprefix $(PROCS_DIR), $(PROCS_LST))

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST) $(EXEC) $(PROCS))
OBJS		=	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HDRS_LST	=	minishell.h parser.h environment.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HDRS_LST))

LIBFT_DIR	=	./libft/
LIBFT		=	$(LIBFT_DIR)libft.a
LIBFT_HDRS	=	$(LIBFT_DIR)includes/

INCLUDES	=	-I $(HDRS_DIR) -I $(LIBFT_HDRS)

RL_LIB		=	-L/usr/include -lreadline

CC			=	gcc
CFLAGS		=	-g

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
