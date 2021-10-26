NAME		=	minishell

SRCS_DIR	=	./srcs/
SRCS_LST	=	main.c	input.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS		=	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HDRS_LST	=	minishell.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HDRS_LST))

INCLUDES	=	-I $(HDRS_DIR)

RL_LIB		=	-L/usr/include -lreadline

CC			=	gcc
CFLAGS		=	-g

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ $(RL_LIB) -o $@

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
