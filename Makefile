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

#NAME = push_swap
#NAMEB = checker
#SRC = push_swap.c ft_error.c ft_find.c ft_lst.c ft_p.c ft_r.c ft_rr.c ft_s.c ft_sort.c ft_stack.c ft_place.c ft_libft.c ft_operation.c
#SRC_B = checker.c ft_error.c ft_find.c ft_lst.c ft_p.c ft_r.c ft_rr.c ft_s.c ft_stack.c ft_libft.c
#OBJ = ${SRC:.c=.o}
#OBJ_B = ${SRC_B:.c=.o}
#CC = cc
#CFLAGS = -Wall -Wextra -Werror -g
#LIBFT = libft/libft.a
#
#all: $(NAME)
#
#%.o : %.c
#	@$(CC) -c $(CFLAGS) $< -o $@
#
#$(LIBFT):
#	@make -C libft
#
#$(NAME): $(LIBFT) $(OBJ)
#	@echo "Make PUSHSWAP"
#	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o push_swap
#
#bonus: $(NAMEB)
#
#$(NAMEB): $(LIBFT) $(OBJ_B)
#	@echo "Make PUSHSWAP BONUS"
#	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) -o checker
#
#clean:
#	@echo "Clean .o files"
#	@make clean -C libft
#	@rm -f $(OBJ) $(OBJ_B)
#
#fclean: clean
#	@echo "Clean ev./erything"
#	@make fclean -C libft
#	@rm -f $(NAME) checker
#
#re: fclean all
#
#.PHONY: all bonus clean fclean re libft