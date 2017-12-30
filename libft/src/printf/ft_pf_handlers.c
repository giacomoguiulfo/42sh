/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:26:07 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:44:30 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

void	ft_prec_nums(t_info *pfinfo, char **str)
{
	char *new;
	char extra;
	char *orig;

	orig = *str;
	if (pfinfo->prec == 0 && !ft_strcmp("0", *str))
	{
		**str = '\0';
		return ;
	}
	if (pfinfo->prec == -1)
		pfinfo->prec = 1;
	if ((size_t)pfinfo->prec < ft_strlen(*str))
		return ;
	extra = (!ISDIGIT((*str)[0]) && pfinfo->spec == 'd') ? (*str)[0] : 0;
	if (extra)
		(*str)++;
	new = ft_strnew(pfinfo->prec + !!extra);
	ft_memset(new + !!extra, '0', pfinfo->prec - ft_strlen(*str));
	ft_strcpy(new + pfinfo->prec - ft_strlen(*str) + !!extra, *str);
	if (extra)
		new[0] = extra;
	free(orig);
	*str = new;
}

void	ft_prec_handle(t_info *pfinfo, char **str)
{
	if (pfinfo->prec == -1)
		return ;
	if (ft_strlen(*str) <= (size_t)pfinfo->prec)
		return ;
	(*str)[pfinfo->prec] = '\0';
}

void	ft_right_just(t_info *pfinfo, char **str, char *new)
{
	char extra;

	extra = 0;
	if (pfinfo->flags & ZER)
	{
		extra = (!ISDIGIT((*str)[0]) && pfinfo->spec == 'd') ? (*str)[0] : 0;
		ft_memset(new, '0', pfinfo->width - ft_strlen(*str) + !!extra);
		if (extra)
		{
			new[0] = extra;
			(*str)[0] = '0';
		}
	}
	else
	{
		ft_memset(new, ' ', pfinfo->width - ft_strlen(*str));
		if ((pfinfo->flags & POS) && **str != '-')
			new[pfinfo->width - ft_strlen(*str)] =
												((*str)[0] == '-') ? '-' : '+';
	}
	ft_strcpy(new + pfinfo->width - ft_strlen(*str) + !!extra, *str + !!extra);
}

void	ft_pad_handle(t_info *pfinfo, char **str)
{
	char	*new;

	if (pfinfo->width == 0 || ft_strlen(*str) >= (size_t)pfinfo->width)
		return ;
	new = ft_strnew(pfinfo->width);
	if (pfinfo->flags & LFT)
	{
		ft_strcpy(new, *str);
		ft_memset(new + ft_strlen(*str), ' ', pfinfo->width - ft_strlen(*str));
	}
	else
		ft_right_just(pfinfo, str, new);
	free(*str);
	*str = new;
	return ;
}
