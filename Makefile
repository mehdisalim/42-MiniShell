NAME	=	minishell

SRCS	=	src/main.c src/test.c

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C ft_printf
	@make -C libft
	$(CC) $(CFLAGS) $^ libft/libft.a ft_printf/libftprintf.a -o $@

%.o		:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	@make clean -C libft
	@make clean -C ft_printf
	@$(RM) *.o

fclean	:	clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@$(RM) $(NAME)

re		: fclean	all
