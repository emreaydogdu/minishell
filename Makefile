NAME	=	minishell
CC		=	cc
RL		=	-lreadline
CFLAGS	=	#-Wall -Wextra -Werror
RM		=	rm -f -r

SRCC	=	minishell.c lexer.c
OBJD	=	obj
SRCD	=	src
SRCS	=	$(addprefix $(SRCD)/,$(SRCC))
OBJS	=	$(addprefix $(OBJD)/,$(SRCC:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(RL) $(OBJS) -o $(NAME)
			@echo "Compile program"

$(OBJD)/%.o: $(SRCD)/%.c
			@mkdir -p $(OBJD)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJD)
			@echo "Remove object files"

fclean:		clean
			@$(RM) $(NAME)
			@echo "Remove program"

re:			fclean all

.PHONY:		all clean fclean re
