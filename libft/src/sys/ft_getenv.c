/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:42:15 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 21:44:24 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char *ft_getenv(char **env, char *key)
{
	if (!env)
		return (NULL);
	while (*env)
	{
		if (ft_strcmp(*env, key) == '=' &&
			ft_strlen(key) == ft_strlenchr(*env, '='))
			return (*env + ft_strlen(key) + 1);
		env++;
	}
	return (NULL);
}
