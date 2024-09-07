CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude/

NAME = minishell

LIBFT = libft

FILES = \
	src/main.c \
	src/ft_free.c \
	src/ft_error.c \
	src/builtins/pwd/ft_pwd.c

OBJS = ${FILES:.c=.o}


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)/libft.a

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
