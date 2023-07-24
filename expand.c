/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:44:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/24 10:48:17 by onaciri          ###   ########.fr       */
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
	//t_env	*var;
	char	**cp;
	size_t		i;
	char	*tmp;

	if (!env)
		return (ft_strdup(""));	
	tmp = ft_substr(str, start, end - start);
	//var = env;
	while (env)
	{
		i = -1;
		while (env->var[++i] && env->var[i] != '=');

		if (!ft_strncmp(tmp, env->var, ft_strlen(tmp)) && i == ft_strlen(tmp))
		{
			free(tmp);
			tmp = ft_substr(env->var, i + 1, ft_strlen(env->var) - ft_strlen(tmp));
			if (is_quote(str, start) == 2)
				return (tmp);
			cp = ft_split(tmp, ' ');
			free(tmp);
			tmp = ft_strdup(cp[0]);
			return(free_2d(cp), tmp);
		}
		env = env->next;
	}
	return (free(tmp), ft_strdup(""));
}

void	rem_dollare(char *str)
{
	int	k;
	int	j;


	k = 0;
	j = 0;
	while (str[k])
	{
		
		if (str[k] == '$' && str[k + 1] && (str[k + 1] == '$' || ft_isdigit(str[k + 1])))
		{
			str[j] = ' ';
			j++;
			k += 2;
		}
		str[j] = str[k];
		j++;
		k++;
	}
	str[j] = '\0';
}

int	ft_strmerge(char **str, int i, int j, t_env *env)
{
	char	*str_bef;
	char	*str_aft;
	char	*tmp2;
	int		z;

	while ((*str)[++i])
		if ((!ft_isalnum((*str)[i]) && (*str)[i] != 95) || (*str)[i] == '$')
			break;
	str_bef = ft_substr(*str, 0, j - 1);
	str_aft = ft_substr(*str, i, ft_strlen(*str) - j);
	
	tmp2 = ft_findvar(*str, j, i, env);
	free(*str);
	*str = ft_strjoin(str_bef, tmp2);
	z = ft_strlen(*str);
	tmp2 = ft_strjoin(*str, str_aft);
	*str = tmp2;
	if (z - 1 < 0)
		return (0);
	return (z - 1);
}

int	do_expand(char *str, int i)
{	
	while (--i >= 0 && str[i])
		if (str[i] != ' ')
			break;
	if (i <= 0)
	{
		if (syt_val(str) == 2)
			return (0);
	}
	else
		if (syt_val(str + (i - 1)) == 2)
			return (0);
	return (1);
}

char   *ft_expand(char *str, t_env *env, int v)
{
    int i;

    i = 0;
    rem_dollare(str);
	while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] != '"' && str[i +1] != ' ')
		{
			if (is_quote(str, i) != 1 && do_expand(str , i))
				i = ft_strmerge(&str, i, i + 1, env);
			else if (v)
				i = ft_strmerge(&str, i, i + 1, env);
		}
		if (str[i] && str[i] != '$' && is_quote(str, i) != 1)
			i++;
	}
	return (str);
}