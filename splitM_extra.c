/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitM_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:17:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/03 07:23:55 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

char	**extra_check(char *str)
{
	char	**ret;

	ret = ft_split(str, ' ');
	free(str);
	if (!ret)
		return (NULL);
	else
		return (ret);
}
