NAME		=	libft.a

SRCS_DIR	=	./srcs/
SRCS_LST	=	ft_strlen.c		ft_strncmp.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS		=	$(SRCS:.c=.o)

HDRS		=	./includes/libft.h

INCLUDES	=	-I ./includes/

CC			=	CC
CFLAGS		=	-Wall -Werror -Wextra -g3

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rcs $@ $^

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
