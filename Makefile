CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude/

NAME = minishell

LIBFT = libft
GNL = get_next_line

FILES = \
	src/main.c \
	src/ft_free.c \
	src/ft_print.c \
	src/builtins/pwd/ft_pwd.c

OBJS = ${FILES:.c=.o}


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(GNL)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)/libft.a $(GNL)/gnl.a

clean:
	make -C $(LIBFT) clean
	make -C $(GNL) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	make -C $(GNL) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
