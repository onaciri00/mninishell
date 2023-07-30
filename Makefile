SRC =   h_error.c genarl.c main.c splitM.c  quote.c expand.c o_file.c free.c execution.c #  c.c

HEADER = mshell.h

HEADER = mshell.h

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

NAME = minishell

LIB = -Llibft -lft 

all: $(NAME) runlibft

$(NAME): $(SRC) $(HEADER)
	cc $(CFLAGS) $(SRC) $(LIB) -lreadline -o $(NAME)

runlibft:
	make -C libft
clean:
	rm -rf $(NAME) 
fclean: clean

re: clean all

