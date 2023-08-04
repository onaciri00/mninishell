/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:44:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/04 16:20:29 by onaciri          ###   ########.fr       */
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

void	rm_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
			str[i] = str[i + 1];
	str[i] = '\0';
}

char	**in_path(t_env *env)
{
	char	**path;

	while (env && !ft_strnstr(env->key, "PATH", ft_strlen("PATH")))
		env = env->next;
	if (!env)
		return (NULL);
	path = ft_split(env->value, ':');
	return (path);
}

char	*ft_path(char *path_cmd, t_env *env)
{
	char	**path;
	char	*cmd1;
	char	*sub_path;
	int		i;

	i = 0;
	if (!path_cmd)
		return (NULL);
	if (access(path_cmd, X_OK) == 0)
		return (path_cmd);
	if (path_cmd[0] == '/')
		return (NULL);
	if (path_cmd[0] == '\\')
		rm_slash(path_cmd);
	i = -1;
	path = in_path(env);
	if (!path)
		return (NULL);
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

void	children(t_lexer *cmd, char **env,  int i, int o_out)
{
	char	*path;
	int		fd[2];

	if (pipe(fd) == -1)
		(write(1, "ERROR:pipe probleme", 20), exit(127));
	cmd->id = fork();
	if (cmd->id == -1)
		(write(1, "ERROR:pipe probleme", 20), exit(127));
	if (cmd->id == 0)
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
		if (is_built(cmd->cmd[0]))
		{
			execute_builtins(cmd);
			exit(0);
		}
		else
		{
			path = ft_path(cmd->cmd[0], cmd->env);
            if (!path)
                (write(1, "ERROR:path probleme", 20), exit(1));
            if (execve(path, cmd->cmd, env) == -1)
            (write(1, "ERROR:path probleme", 20), exit(1));
		}
	}
	else
	{
		if (cmd->inf > -1)
            close(cmd->inf);
        if (cmd->outf > -1)
            close(cmd->outf);
        close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}