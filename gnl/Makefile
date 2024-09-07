CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = gnl.a

FILES = \
	get_next_line.c \
	get_next_line_utils.c

OBJS = ${FILES:.c=.o}


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	ar r $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
