ENV		=	env
PWD		=	pwd

ALL		=	$(ENV) $(PWD)

SRCS	=	$(addsuffix .c, $(ALL))

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-g

all: $(ALL)

$(ENV) : $(ENV).o
	$(CC) $(CFLAGS) $< -o $@

$(PWD) : $(PWD).o
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(ALL)

re: fclean all

.PHONY = clean fclean re
