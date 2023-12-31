/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_need.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:23:00 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/05 10:23:43 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

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

	while (env && ft_strcmp(env->key, "PATH"))
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
