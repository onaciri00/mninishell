/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exeuction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:13:02 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/03 12:04:04 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

int is_built(char *str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (1);
	return (0);
}

void	pipex(t_lexer  *cmd, char **env, int i)
{
	t_lexer	*lst;
	int file;
	int status;
	int out_file;

	file = dup(STDIN_FILENO);
	out_file = dup(STDOUT_FILENO);
	lst = cmd;
	while (cmd)
	{
		if (!cmd->next)
			i = 1;
		if (cmd->inf != -1 && cmd->outf != -1 && cmd->cmd && cmd->cmd[0])
			children(cmd, env, i, out_file);
		cmd = cmd->next;
	}
	while(lst)
	{ 
		if (lst->inf != -1 && lst->outf != -1)
			waitpid(lst->id, &status, 0);
		lst = lst->next;
	}
	if (WIFEXITED(status))
		exit_s = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_s = WTERMSIG(status);
	dup2(file, STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
}
