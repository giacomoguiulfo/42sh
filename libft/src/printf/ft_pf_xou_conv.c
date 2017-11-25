/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_xou_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:53:29 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:46:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

uintmax_t	ft_xou_len(char length, va_list ap)
{
	if (length == hh)
		return ((unsigned char)va_arg(ap, int));
	if (length == h)
		return ((unsigned short)va_arg(ap, int));
	if (length == l)
		return (va_arg(ap, unsigned long));
	if (length == ll)
		return (va_arg(ap, unsigned long long));
	if (length == j)
		return (va_arg(ap, uintmax_t));
	if (length == z)
		return (va_arg(ap, size_t));
	return (va_arg(ap, unsigned int));
}

void		ft_handle_alt(t_info *pfinfo, char **str)
{
	char *new;

	if (!(IS_XO(pfinfo->spec) || pfinfo->spec == 'p' || pfinfo->spec == 'b'))
		return ;
	new = ft_strdup(*str);
	if (pfinfo->spec == 'p')
		ft_insrt_to_str(&new, "0x");
	else if (pfinfo->flags & HTG)
	{
		if (pfinfo->spec == 'b' && ft_strcmp("0", *str) &&
														ft_strcmp("\0", *str))
			ft_insrt_to_str(&new, "0b");
		else if (IS_X(pfinfo->spec) && ft_strcmp("0", *str) &&
														ft_strcmp("\0", *str))
			ft_insrt_to_str(&new, "0x");
		else if (IS_O(pfinfo->spec) && **str != '0')
			ft_insrt_to_str(&new, "0");
	}
	free(*str);
	*str = new;
}

void		ft_x_toupper(char *str, char spec)
{
	if (spec != 'X')
		return ;
	while (*str)
	{
		if (ISALPHA(*str))
			*str = TOUPPER(*str);
		str++;
	}
}

void		ft_handle_xou(char **str, t_info *pfinfo)
{
	if (pfinfo->flags & ZER && pfinfo->prec == 0)
		pfinfo->flags ^= ZER;
	if (pfinfo->prec == 0 && !ft_strcmp(*str, "0"))
		**str = '\0';
	ft_prec_nums(pfinfo, str);
	if (pfinfo->flags & ZER && pfinfo->spec == 'p')
	{
		pfinfo->width = MAX(pfinfo->width - 2, 0);
		ft_pad_handle(pfinfo, str);
	}
	else if (pfinfo->flags & ZER && pfinfo->flags & HTG && (IS_X(pfinfo->spec)
														|| pfinfo->spec == 'b'))
	{
		pfinfo->width = MAX(pfinfo->width - 2, 0);
		ft_pad_handle(pfinfo, str);
	}
	ft_handle_alt(pfinfo, str);
	if (!(pfinfo->flags & ZER && pfinfo->flags & HTG && (IS_X(pfinfo->spec)
								|| pfinfo->spec == 'p' || pfinfo->spec == 'b')))
		ft_pad_handle(pfinfo, str);
	ft_x_toupper(*str, pfinfo->spec);
}
