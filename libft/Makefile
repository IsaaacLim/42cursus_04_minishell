NAME		=	libft.a

SRCS_DIR	=	./srcs/
SRCS_LST	=	ft_atoi.c			ft_bzero.c			ft_calloc.c			\
				ft_isalpha.c		ft_isdigit.c		ft_lstadd_back.c	\
				ft_lstclear.c		ft_lstdelone.c		ft_lstlast.c		\
				ft_lstnew.c			ft_lstsize.c		ft_memcpy.c			\
				ft_putendl_fd.c		ft_putstr_fd.c		ft_split.c			\
				ft_strchr.c			ft_strdup.c			ft_strjoin.c		\
				ft_strjoin_bonus.c	ft_strlen.c			ft_strncmp.c		\
				ft_substr.c
						
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
	@ar rcs $@ $^
	@echo " $(YELLOW)$(NAME) $(GREEN)object files created"
	@echo " $(BLUE)$(NAME)$(GREEN) created$(RESET)"

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJS)
	@echo "$(RED)removed $(YELLOW)$(NAME) $(RED)object files $(RESET)"

fclean:		clean
	@rm -rf $(NAME)
	@echo "$(RED)removed $(BLUE)$(NAME)$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re

RED		=	\033[00;31m
YELLOW	=	\033[03;33m
GREEN	=	\033[00;32m
BLUE	=	\033[01;36m
RESET	=	\033[0m
