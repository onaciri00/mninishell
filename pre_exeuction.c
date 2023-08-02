/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exeuction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:13:02 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/02 14:11:09 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

int	built_run(t_lexer *cmd, int i)
{
	int	fd[2];

	if (!i && cmd->inf != 1 && cmd->outf > -1)
	{
		if (pipe(fd) == -1);
			perror("pipe: ");
		dup2(fd[1], STDIN_FILENO);
		//built in
		dup2(fd[0], )
	}
}

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

	file = dup(STDIN_FILENO);
	lst = cmd;
	while (cmd)
	{
		if (!cmd->next)
			i = 1;
		if (cmd->inf != -1 && cmd->outf != -1 && cmd->cmd && cmd->cmd[0])
		{	
			if (is_built(cmd->cmd[0]))
				run_built(cmd, i);
			else
				children(cmd, env,  i);
		}
		cmd = cmd->next;
	}
	while(lst)
	{ 
		if (!is_built(cmd->cmd[0]) && cmd->file != -1 && cmd->outf != -1)
			waitpid(lst->id, &status, 0);
		lst = lst->next;
	}
	if (WIFEXITED(status))
		exit_s = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_s = WTERMSIG(status);
	dup2(file, STDIN_FILENO);
}


void pre_exe(t_lexer  *cmd, char **env)
{
    if (is_built(cmd->cmd[0]))
		return ;
	else
		pipex(cmd, env, 0);
}