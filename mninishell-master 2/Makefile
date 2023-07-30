#SRC =   h_error.c genarl.c main.c splitM.c  quote.c expand.c o_file.c free.c execution.c  builtins/pwd.c builtins/main.c builtins/utils.c builtins/echo.c builtins/cd.c builtins/exit.c builtins/execute_builtins.c builtins/handler_signals.c

SRC= *.c libft/*.c builtins/*.c

HEADER = mshell.h

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

NAME = minishell

LIB = -Llibft -lft 

all: $(NAME) #runlibft

$(NAME): $(SRC) $(HEADER)
	cc $(CFLAGS) $(SRC) $(LIB) -lreadline -L/goinfre/sel-ouar/homebrew/Cellar/readline/8.2.1/lib -I/goinfre/sel-ouar/homebrew/Cellar/readline/8.2.1/include -o $(NAME)

runlibft:
	make -C libft
clean:
	rm -rf $(NAME) 
fclean: clean

re: clean all

