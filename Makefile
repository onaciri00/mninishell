SRC =   h_error.c genarl.c main.c splitM.c  quote.c expand.c o_file.c free.c execution.c env.c #  c.c

HEADER = mshell.h

HEADER = mshell.h

CFLAGS = -Wall -Wextra -Werror -lreadline 
#-fsanitize=address -g3

NAME = minishell

LIB = -Llibft -lft 

all: $(NAME) runlibft

$(NAME): $(SRC) $(HEADER)
	cc $(CFLAGS) $(SRC) $(LIB)  -o $(NAME) -L /Users/onaciri/Desktop/readline-8.2

runlibft:
	make -C libft
clean:
	rm -rf $(NAME) 
fclean: clean

re: clean all

