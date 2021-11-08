NAME		=	libft.a

SRCS_DIR	=	./srcs/
SRCS_LST	=	ft_bzero.c		ft_calloc.c		ft_lstadd_back.c	\
				ft_lstclear.c	ft_lstdelone.c	ft_lstlast.c		\
				ft_lstnew.c		ft_memcpy.c		ft_split.c			\
				ft_strlen.c		ft_strncmp.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS		=	$(SRCS:.c=.o)

HDRS		=	./includes/libft.h

INCLUDES	=	-I ./includes/

CC			=	gcc
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
