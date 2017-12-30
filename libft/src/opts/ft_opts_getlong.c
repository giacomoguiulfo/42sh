/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts_getlong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 00:35:35 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/22 18:54:46 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"
#include "str.h"
#include <stddef.h>

t_opt	*ft_opts_getlong(t_opt opt_map[], char *name)
{
	int	i;

	i = 0;
	while (opt_map[i].c)
	{
		if (ft_strequ(opt_map[i].name, name))
			return (&opt_map[i]);
		i++;
	}
	return (NULL);
}
