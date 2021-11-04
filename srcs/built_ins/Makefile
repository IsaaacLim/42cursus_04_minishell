CD		=	cd
ENV		=	env
PWD		=	pwd

ALL		=	$(CD) $(ENV) $(PWD)

SRCS	=	$(addsuffix .c, $(ALL))

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-g

all: $(ALL)

$(CD) : $(CD).o
	$(CC) $(CFLAGS) $< -o $@

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
