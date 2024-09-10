CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude/
LFLAGS = -lreadline

NAME = minishell

LIBFT = libft

FILES = \
	src/main.c \
	src/ft_parse.c \
	src/ft_quote_parser.c \
	src/gnl.c \
	src/ft_free.c \
	src/ft_print.c \
	src/ft_signals.c \
	src/builtins/pwd/ft_pwd.c \
	src/builtins/echo/ft_echo.c \
	src/builtins/cd/ft_cd.c \
	src/builtins/env/ft_env.c \
	src/builtins/unset/ft_unset.c \
	src/builtins/export/ft_export.c

OBJS = ${FILES:.c=.o}


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT)/libft.a

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
