ECHO	=	echo
ENV		=	env
EXPORT	=	export
PWD		=	pwd

ALL		=	$(ECHO) $(ENV) $(EXPORT) $(PWD) 

SRCS	=	$(addsuffix .c, $(ALL))

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-g

all: $(ALL)

$(ECHO) : $(ECHO).o
	$(CC) $(CFLAGS) $< -o $@

$(ENV) : $(ENV).o
	$(CC) $(CFLAGS) $< -o $@

$(EXPORT) : $(EXPORT).o
	$(CC) $(CFLAGS) $< -o $@

$(PWD) : $(PWD).o
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(ALL)

re: fclean all

.PHONY = clean fclean re
