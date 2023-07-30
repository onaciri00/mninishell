/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:44:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/28 19:52:25 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	ft_free(char **dev, char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	i = 0;
	while (dev[i])
	{
		free(dev[i]);
		i++;
	}
	free(dev);
}


char	*ft_strjoinp(char const *s1, char const *s2)
{
	char	*str;
	size_t	b;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	j = ft_strlen(s1);
	j = j + ft_strlen(s2);
	i = 0;
	b = 0;
	if (!s1[0] && !s2[0])
		return (ft_strdup(""));
	str = (char *) malloc(sizeof(char) * j + 1);
	if (!str)
		return (0);
	while (i <= j && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (i <= j && s2[b] != '\0')
		str[i++] = s2[b++];
	str[i] = '\0';
	return (str);
}

char	*ft_path(char *path_cmd, char **env)
{
	//char	**dev;
	char	**path;
	char	*cmd1;
	char	*sub_path;
	int		i;

	i = 0;
	if (access(path_cmd, X_OK) == 0)
		return (path_cmd);
	while (env[i] && !ft_strnstr(env[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (!env[i])
		showerror("the path is gone");
	path = ft_split(env[i], ':');
	i = -1;
	sub_path = ft_strjoinp(path[0], "/");
	cmd1 = ft_strjoinp(sub_path, path_cmd);
	while ((access(cmd1, X_OK) == -1) && path[++i] != NULL)
	{
		free(sub_path);
		free(cmd1);
		sub_path = ft_strjoinp(path[i], "/");
		cmd1 = ft_strjoinp(sub_path, path_cmd);
	}
	return (free(sub_path), cmd1);
}

void	children(t_lexer *cmd, char **env, int first, int i)
{
	int		id;
	char	*path;
	int		fd[2];
	int o_out = dup(STDOUT_FILENO);

	if (pipe(fd) == -1)
		(write(1, "ERROR:pipe probleme", 20), exit(1));
	id = fork();
	if (id == -1)
		(write(1, "ERROR:fork probleme", 20), exit(1));
	if (id == 0)
	{
		// signal(SIGINT, sigint);

		// handler_signals1();
		// printf("lssss\n");
		close(fd[0]);
		if (cmd->inf == -2 && !first)
			cmd->inf = fd_pipe();
		else if (cmd->inf >= 0)
			dup2(cmd->inf, STDIN_FILENO);
		if (cmd->outf < 0 && !i)
			dup2(fd[1], STDOUT_FILENO);
		else if (cmd->outf >= 0)
		{
			dup2(cmd->outf, STDOUT_FILENO);
		}
		else if (cmd->outf == -2 && i)
			 dup2(o_out, STDOUT_FILENO);
		path = ft_path(cmd->cmd[0], env);
		if (execve(path, cmd->cmd, env) == -1)
			(write(2, "ERROR:execve probleme\n", 23), exit(127));
	}
	else
	{
		close(fd[1]);
		wait(0);
		//printf("dol\n");
		if (cmd->outf >= 0)
		{
			dup2(cmd->outf, STDIN_FILENO);
			close(fd[0]);
		}
		else if (cmd->outf < 0) 
			dup2(fd[0], STDIN_FILENO);
	}
}

void	pipex(t_lexer  *cmd, char **env)
{
	int	i;
	int	j;
	int file;

	i = 0;
	j = 0;
	file = dup(STDIN_FILENO);
	while (cmd)
	{
		if (!cmd->next)
			i = 1;
		if (cmd->inf != -1)
		{	
			children(cmd, env, cmd->outf, i);
			close(cmd->inf);
		}
		j++;
		cmd = cmd->next;
	}
	//printf("chilsd\n");
	dup2(file, STDIN_FILENO);
}