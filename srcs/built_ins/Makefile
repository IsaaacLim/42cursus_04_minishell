ECHO	=	echo
ENV		=	env
EXPORT	=	export
PWD		=	pwd

ALL		=	$(ECHO) $(ENV) $(EXPORT) $(PWD) 

OBJS	=	$(addsuffix .o, $(ALL))


CC		=	gcc
CFLAGS	=	-g -Wall -Wextra -Werror

all: $(ALL)
	@echo " $(YELLOW)$(ALL) $(GREEN)object files created"
	@echo "$(BLUE)$(ALL)$(GREEN) created$(RESET)"

$(ECHO) : $(ECHO).o
	@$(CC) $< -o $@

$(ECHO).o : $(ECHO).c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(ENV) : $(ENV).o
	@$(CC) $< -o $@

$(ENV).o : $(ENV).c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(EXPORT) : $(EXPORT).o
	@$(CC) $< -o $@

$(EXPORT).o : $(EXPORT).c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(PWD) : $(PWD).o
	@$(CC) $< -o $@

$(PWD).o : $(PWD).c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean :
	@rm -f $(OBJS)
	@echo "$(RED)removed $(YELLOW)$(ALL)$(RED)object files $(RESET)"

fclean : clean
	@rm -f $(ALL)
	@echo "$(RED)removed $(BLUE)$(ALL)$(RESET)"

re: fclean all

.PHONY: clean fclean re

RED		=	\033[00;31m
YELLOW	=	\033[03;33m
GREEN	=	\033[00;32m
BLUE	=	\033[01;36m
RESET	=	\033[0m
