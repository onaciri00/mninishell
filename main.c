/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:44:20 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/04 08:52:06 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	main(int ac, char *av[], char *env[])
{
	char	*str;
	t_lexer	*cmd;
	t_env	*var;

	if (ac != 1 || !ft_strnstr(av[0], "./minishell", 11))
		return (1);
	var = full_env(env);
	exit_s = 0;
	while (1)
	{
		str = readline("minshell: ");
		if (!str)
			exit(0);
		if (str[0])
		{
			add_history(str);
			cmd = ft_start(&str, var, 0);
			pipex(cmd, env, 0);
			free_all(cmd);
		}
		free(str);
		//system("leaks minishell");
	}
}
