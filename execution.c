/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:44:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/26 09:42:46 by onaciri          ###   ########.fr       */
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
	char	**dev;
	char	**path;
	char	*cmd1;
	char	*sub_path;
	int		i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (!env[i])
		showerror("the path is gone");
	dev = ft_split(path_cmd, ' ');
	path = ft_split(env[i], ':');
	i = -1;
	sub_path = ft_strjoinp(path[0], "/");
	cmd1 = ft_strjoinp(sub_path, dev[0]);
	while ((access(cmd1, F_OK) == -1) && path[++i] != NULL)
	{
		free(sub_path);
		free(cmd1);
		sub_path = ft_strjoinp(path[i], "/");
		cmd1 = ft_strjoinp(sub_path, dev[0]);
	}
	return (ft_free(dev, path), free(sub_path), cmd1);
}

void	children(char **str, char **env, int fdout, int i)
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
		close(fd[0]);
		if (fdout < 0 && !i)
			dup2(fd[1], STDOUT_FILENO);
		else if (fdout > 0)
			dup2(fdout, STDOUT_FILENO);
		else if (fdout < 0 && i)
			 dup2(o_out, STDOUT_FILENO);
		path = ft_path(str[0], env);
		if (execve(path, str, env) == -1)
			write(1, "ERROR:execve probleme", 22);
	}
	else
	{
		close(fd[1]);
		wait(0);
		if (fdout > -1)
		{
			dup2(fdout, STDIN_FILENO);
			close(fd[0]);
		}
		else
			dup2(fd[0], STDIN_FILENO);
	}
}

// void	final_child(char **str, char **env, int fdout)
// {
// 	char *path;
// 	//int		id;

 //	int o_out = dup(STDOUT_FILENO);
// 	if (fdout < 0)
// 		return ;
// 	if (fdout != 1)
// 		dup2(fdout, STDOUT_FILENO);
// 	else
// 		dup2(o_out, STDOUT_FILENO);
// 	path = ft_path(str[0], env);
// 	printf("%d\n", fdout);
// 	if (execve(path, str, env) == -1)
// 		(write(1, "ERROR:execve probleme", 22), exit(1));
// }

void	pipex(t_lexer  *cmd, char **env)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (!cmd->next)
			i = 1;
		dup2(cmd->inf, STDIN_FILENO);
		children(cmd->cmd, env, cmd->outf, i);
		cmd = cmd->next;
	}
	printf("all good\n");
	//final_child(cmd->cmd, env, cmd->outf);
}