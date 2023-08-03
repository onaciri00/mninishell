/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:43:30 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/03 08:07:28 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

char	**env_split(char *env)
{
	char	**s;

	s = malloc(sizeof(char *) * 2);
	if (!s)
		return (NULL);
	s[0] = ft_substr(env, 0, ft_strchr(env, '=') - env);
	s[1] = ft_strdup(env + (ft_strchr(env, '=') - env) + 1);
	return (s);
}

void	add_env(t_env **var, char *env)
{
	t_env	*lst;
	t_env	*new;
	char	**str;

	lst = (*var);
	while (lst->next)
	lst = lst->next;
	new = malloc(sizeof(t_env));
	new->next = NULL;
	str = env_split(env);
	new->key = ft_strdup(str[0]);
	free(str[0]);
	new->value = ft_strdup(str[1]);
	free(str[1]);
	free(str);
	lst->next = new;
}

void	env_new(t_env **var, char *env)
{
	char	**str;

	if (!*var)
	{
		(*var) = malloc(sizeof (t_env));
		str = env_split(env);
		(*var)->key = ft_strdup(str[0]);
		free(str[0]);
		(*var)->value = ft_strdup(str[1]);
		free(str[1]);
		free(str);
		(*var)->next = NULL;
	}
	else
		add_env(var, env);
}

t_env	*full_env(char **env)
{
	t_env	*var;
	int		i;

	i = -1;
	var = NULL;
	while (env[++i])
	{
		env_new(&var, env[i]);
	}
	return (var);
}
