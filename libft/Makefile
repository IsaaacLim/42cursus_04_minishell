NAME		=	libft.a

SRCS_DIR	=	./srcs/
SRCS_LST	=	ft_bzero.c		ft_calloc.c		ft_lstadd_back.c	\
				ft_lstclear.c	ft_lstdelone.c	ft_lstlast.c		\
				ft_lstnew.c		ft_lstsize.c	ft_memcpy.c			\
				ft_split.c		ft_strdup.c		ft_strjoin.c		\
				ft_strlen.c		ft_strncmp.c	ft_strchr.c 		\
				ft_substr.c		ft_strcpy.c
GNL_LST		=	get_next_line.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST) $(GNL_LST))

OBJS		=	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HDRS_LST	=	libft.h get_next_line.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HDRS_LST))

INCLUDES	=	-I $(HDRS_DIR)

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
