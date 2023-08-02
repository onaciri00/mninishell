/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:44:20 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/01 11:56:04 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mshell.h"
#include <termios.h>

int main(int ac, char *av[], char *env[]) 
{
    char *str;
	t_lexer *cmd;
	// t_file *file;
	t_env	*var;
	 //int i=0;
	// struct termios	origenal;
	// struct termios	fake;
	(void)env;
	 //(void)av;
	// tcgetattr(0, &origenal);
	// tcgetattr(0, &fake);
	// fake.c_lflag &= ~ECHOCTL;
	if (ac != 1 || !ft_strnstr(av[0], "./minishell", 11))
		(void)ac;
	// 	return (1);
	var = full_env(env);
	while (1)
	{
		// tcsetattr(STDIN_FILENO, TCSANOW, &fake);
		// signal(SIGINT, sigint);
		// signal(SIGQUIT, sigquit);
		str = readline("minshell: ");
		// tcsetattr(STDIN_FILENO, TCSANOW, &origenal);
		if (!str)
		{
			write (2, "exit\n", 4);
			exit(10);
		}
		if(str[0])
		{
			add_history(str);
			cmd = ft_start(str, var);
			if (execute_builtins(cmd))
				;
			else
				pipex(cmd, env);
			free_all(cmd);
		}
		free(str);
		// handler_signals();
	// 	while (cmd)
	// 	{
	// 	 	i = -1;
	// 		while (cmd->cmd[++i])
	// 			printf("*%s* ", cmd->cmd[i] /*cmd->file->file*/);
	// 		file = cmd->file;
	// 		printf("\n");
	// 		while (file)
	// 		{
	// 			if (file->file)
	// 				printf("\n********** file ='%s' %d\n", file->file, file->type);
	// 			else	
	// 				printf("********** lim ='%s' %d\n", file->limeter, file->type);
	// 			file = file->next;
	// 		}
	// 		cmd = cmd->next;
	// 	}
	}
}
