SRC =   h_error.c genarl.c main.c splitM.c  quote.c expand.c o_file.c free.c execution.c env.c builtins/cd.c builtins/echo.c \
 builtins/env.c builtins/execute_builtins.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/utils.c  pre_exeuction.c \
 splitM_extra.c #  c.c

HEADER = mshell.h

HEADER = mshell.h

CFLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address -g3

NAME = minishell

LIB = -Llibft -lft 

all: $(NAME) runlibft

$(NAME): $(SRC) $(HEADER)
	cc $(CFLAGS) $(SRC) $(LIB)  -o $(NAME)

runlibft:
	make -C libft
clean:
	rm -rf $(NAME) 
fclean: clean

re: clean all

