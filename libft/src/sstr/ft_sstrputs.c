/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:35:06 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:32:40 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sstrputs(char **sstr)
{
	int i;

	if (!sstr || !*sstr)
		return ;
	i = 0;
	while (sstr[i])
	{
		ft_putendl(sstr[i]);
		i++;
	}
}
