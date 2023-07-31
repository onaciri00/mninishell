/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:44:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/31 09:58:12 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	find_quest(char **str, int i, int sing)
{
	char *num;
	char *tmp;
	char *end;
	int	len;
	
	if (!sing)
		num  = ft_itoa(exit_s);
	else
	{
		num = malloc(2);
		num[0] = '0';
		num[1] = '\0';
	}
	tmp = ft_substr(*str, 0, i);
	end = ft_substr(*str, i + 2, ft_strlen(*str) - i + 2);
	free(*str);
	*str = ft_strjoin(tmp, num);
	tmp = ft_strjoin(*str, end);
	*str = tmp;
	len = ft_strlen(num);
	return (len);
}

char *ft_findvar(char *str, int start, int end, t_env *env)
{
	char	**cp;
	size_t		i;
	char	*tmp;

	if (!env)
		return (ft_strdup(""));	
	tmp = ft_substr(str, start, end - start);
	while (env)
	{
		i = -1;
		if (!ft_strncmp(tmp, env->key, ft_strlen(tmp)) && ft_strlen(env->key) == ft_strlen(tmp))
		{
			free(tmp);
			tmp = ft_substr(env->value, 0, ft_strlen(env->value));
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

int	ft_strmerge(char **str, int i, int j, t_env *env)
{
	char	*str_bef;
	char	*str_aft;
	char	*tmp2;
	int		z;

	while ((*str)[++i])
		if ((!ft_isalnum((*str)[i]) && (*str)[i] != 95) || (*str)[i] == '$' || ft_isdigit((*str)[j]) || (*str)[i] == '@')
			break;
	if ((ft_isdigit((*str)[j]) || (*str)[i] == '$' ||  (*str)[i] == '@') && (*str)[i])
		i++;
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

void	ft_expand(char **str, t_env *env, int v)
{
    int i;
	int	sing;

    i = 0;
	sing = 0;
	while ((*str)[i])
    {
        if ((*str)[i] == '$' && (ft_isalnum((*str)[i + 1]) || (*str)[i +1] == 95 || (*str)[i + 1] == '$' || (*str)[i + 1] == '"' || (*str)[i + 1] =='\'' || (*str)[i + 1] == '@'))
		{
			if (is_quote(*str, i) != 1 && do_expand(*str , i) && v && !(is_quote(*str, i) == 2 && ((*str)[i + 1] == '"' || (*str)[i + 1] == '\'' )))
				i = ft_strmerge(str, i, i + 1, env);
		}
		else if ((*str)[i] == '$' && (*str)[i + 1] == '?' && v)
		{
			i += find_quest(str, i,sing);
			sing++;
		}
		if ((*str)[i])
			i++;
	}
}
