/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:33:21 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/07/28 12:35:07 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

int ft_pwd(void)
{
    char    max_path[1024];

    if(getcwd(max_path, 1024) == NULL)
        return (1);
    printf("%s\n", max_path);
    return (0);
}
