/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:44:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/15 17:27:23 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	env_new(t_env **var, char *env)
{
	t_env	*lst;
	t_env	*new;

	if (!*var)
	{
		(*var) = malloc(sizeof(t_env));
		(*var)->var = env;
		(*var)->next = NULL;
	}
	else
	{
		lst = (*var);
		while (lst->next)
			lst = lst->next;
		new = malloc(sizeof(t_env));
		new->next = NULL;
		new->var = env;
		lst->next = new;
	}
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

char *ft_findvar(char *str, int start, int end, t_env *env)
{
	t_env	*var;
	char	*tmp;

	tmp = ft_substr(str, start, end - start);
	var = env;
	while (var)
	{
		if (ft_strnstr(var->var, tmp, ft_strlen(tmp)))
		{
			free(tmp);
			tmp = ft_substr(var->var, end - (start - 1) , ft_strlen(var->var) - (end - start));
			return (tmp);
		}
		var = var->next;
	}
	return (ft_strdup(""));
}
int	ft_strmerge(char **str, int i, int j, t_env *env)
{
	char	*str_bef;
	char	*str_aft;
	char	*tmp2;
	int		z;

	while ((*str)[++i])
		if ((*str)[i] == ' ' || (*str)[i] == '"' || (*str)[i] == '$' || (*str)[i] == '\'' || syt_val(*str + i))
			break;
	str_bef = ft_substr(*str, 0, j - 1);
	str_aft = ft_substr(*str, i, ft_strlen(*str) - j);
	tmp2 = ft_findvar(*str, j, i, env);
	free(*str);
	*str = ft_strjoin(str_bef, tmp2);
	z = ft_strlen(tmp2);
	tmp2 = ft_strjoin(*str, str_aft);
	*str = tmp2;
	return (j + z - 1);
}

char   *ft_expand(char *str, t_env *env, int dqo, int sqo)
{
    int i;

    i = 0;
    while (str[i])
    {
		if (str[i] == '"' && !sqo)
			dqo++;
		else if (str[i] == '\'' && !dqo)
			sqo++;
		if (sqo == 2 || dqo == 2)
		{
			sqo = 0;
			dqo = 0;
		}
        if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != '"')
		{
			if (sqo != 1)
				i = ft_strmerge(&str, i, i + 1, env) - 1;
			printf("y%d\n", i);
		}
		else if (str[i] == '$' && sqo != 1 && (str[i +1 ] == '$' || str[i + 1] == '"' || !str[i + 1]))
			str[i] = ' ';
		if (str[i])
			i++;
	}
	return (str);
}