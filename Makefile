NAME	=	minishell

SRCS	=	main.c
OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-g

RL_LIB	=	-L/usr/include -lreadline

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ $(RL_LIB) -o $@

# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
