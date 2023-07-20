SRC =   h_error.c genarl.c main.c splitM.c  quote.c expand.c #  c.c

HEADER = mshell.h

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

NAME = minishell

LIB = -Llibft -lft 

all: $(NAME) runlibft

$(NAME): $(SRC)
	cc $(CFLAGS) $(SRC) $(LIB) -lreadline -o $(NAME)

runlibft:
	make -C libft
clean:
	rm -rf $(NAME) 
fclean: clean

re: clean all

