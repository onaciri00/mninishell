/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:44:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/05 10:31:31 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	father(t_lexer *cmd, int fd[2])
{
	if (cmd->inf > -1)
          close(cmd->inf);
     if (cmd->outf > -1)
        close(cmd->outf);
    close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	before_exe(t_lexer *cmd, int fd[2], int o_out, int i)
{
	close(fd[0]);
	if (cmd->inf > -1)
	{	
		dup2(cmd->inf, STDIN_FILENO);
		close(cmd->inf);
	}
	if (cmd->outf > -1)
	{
		dup2(cmd->outf, STDOUT_FILENO);
		close(cmd->outf);
	}
	else if (cmd->outf < 0 && !i)
		dup2(fd[1], STDOUT_FILENO);
	else if (cmd->outf < 0 && i)
		dup2(o_out, STDOUT_FILENO);
	close(fd[1]);
}

void	children(t_lexer *cmd, char **env,  int i, int o_out)
{
	char	*path;
	int		fd[2];

	if (pipe(fd) == -1)
		(perror("minishell: "), exit(127));
	cmd->id = fork();
	if (cmd->id == -1)
		(perror("minishell: "), exit(127));
	if (cmd->id == 0)
	{
		before_exe(cmd, fd, o_out, i);
		if (is_built(cmd->cmd[0]))
		{
			execute_builtins(cmd);
			exit(0);
		}
		else
		{
			path = ft_path(cmd->cmd[0], cmd->env);
            if (execve(path, cmd->cmd, env) == -1)
				(perror("minishell: "), exit(127));
		}
	}
	else
		father(cmd, fd);

}