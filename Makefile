NAME		=	minishell

SRCS_DIR	=	./srcs/
SRCS_LST	=	main.c				signals.c				utils.c

EXEC_DIR	=	execute/
EXEC_LST	=	execute_utils.c		ft_execute.c			redirection.c
EXEC		=	$(addprefix $(EXEC_DIR), $(EXEC_LST))

PROCS_DIR	=	processes/
PROCS_LST	=	env_validate.c		environment_utils.c		ft_cd.c			\
				export.c			ft_environment.c		ft_exit.c		\
				process.c			unset.c
PROCS		=	$(addprefix $(PROCS_DIR), $(PROCS_LST))

PARSER_DIR	=	parser/
PARSER_LST	=	ft_split_enhanced.c	parse_env_utils.c		parse_env.c		\
				parser_utils.c 		parser_utils2.c			parser.c

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

RL_LIB		=	-L/usr/include -lreadline

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror

BLT_INS_DIR	=	./srcs/built_ins/
BUILT_INS	=	$(BLT_INS_DIR)env

all: $(NAME) $(BUILT_INS)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $^ $(RL_LIB) $(LIBFT) -o $@
	@echo " $(YELLOW)$(NAME) $(GREEN)object files created"
	@echo "$(BLUE)$(NAME)$(GREEN) created$(RESET)"

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT) :
	@make -C $(LIBFT_DIR)

$(BUILT_INS) :
	@make -C $(BLT_INS_DIR)

clean:
	@make clean -C $(BLT_INS_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "$(RED)removed $(YELLOW)$(NAME) $(RED)object files $(RESET)"

fclean:	clean
	@make fclean -C $(BLT_INS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(RED)removed $(BLUE)$(NAME)$(RESET)"

re: fclean all

.PHONY: clean fclean re

RED		=	\033[00;31m
YELLOW	=	\033[03;33m
GREEN	=	\033[00;32m
BLUE	=	\033[01;36m
NOTE	=	\033[02;33m
RESET	=	\033[0m
