NAME	=	minishell
CC		=	cc
RL		=	-lreadline
CFLAGS	=	#-Wall -Wextra -Werror
RM		=	rm -f -r

SRCC	=	minishell.c lexer.c expander.c parser.c printers.c
OBJD	=	obj
SRCD	=	src
SRCS	=	$(addprefix $(SRCD)/,$(SRCC))
OBJS	=	$(addprefix $(OBJD)/,$(SRCC:.c=.o))
LIBFT	=	libft/libft.a

all:		$(NAME)

$(LIBFT):
	@make -C libft

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RL)
			@echo "Compile Minishell"

$(OBJD)/%.o: $(SRCD)/%.c
			@mkdir -p $(OBJD)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJD)
			@make clean -C libft
			@echo "Remove object files"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C libft
			@echo "Remove program"

re:			fclean all

.PHONY:		all clean fclean re