/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandExtra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:22:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/03 15:37:56 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

char    *ft_strextra(char **str)
{
    int     i;
    char	*sp;
	char	*hold;
	char    *clone;

    i = 0;
	if (len_2d(str) == 1)
		return (ft_strdup(str[0]));
	if (!len_2d(str))
		return (NULL);
	while (str[i])
    {
        if (str[i + 1])
        {
    		sp = ft_strdup(" ");
			hold = ft_strdup(str[i]);
			clone = ft_strjoin(hold, sp);
			hold = ft_strdup(str[i + 1]);
			clone = ft_strjoin(clone, hold);
		}
		if (!clone)
            return (NULL);
        i++;
    }
    return (clone);
}