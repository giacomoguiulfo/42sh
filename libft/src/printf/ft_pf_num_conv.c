/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_num_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:05:31 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:17:27 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

intmax_t	ft_int_len(char length, va_list ap)
{
	if (length == hh)
		return ((signed char)va_arg(ap, int));
	if (length == h)
		return ((short)va_arg(ap, int));
	if (length == l)
		return (va_arg(ap, long));
	if (length == ll)
		return (va_arg(ap, long long));
	if (length == j)
		return (va_arg(ap, intmax_t));
	if (length == z)
		return (va_arg(ap, ssize_t));
	return (va_arg(ap, int));
}

void		ft_num_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	intmax_t	ival;
	char		*str;

	if (pfinfo->spec == 'D')
		pfinfo->length = l;
	if (pfinfo->spec == 'i' || pfinfo->spec == 'D')
		pfinfo->spec = 'd';
	ival = ft_int_len(pfinfo->length, ap);
	str = ft_imaxtoa(ival);
	if (pfinfo->prec != -1 && pfinfo->flags & ZER)
		pfinfo->flags ^= ZER;
	if (pfinfo->prec == 0 && !ft_strcmp("0", str))
		*str = '\0';
	if (((pfinfo->flags & POS || pfinfo->flags & INV) && str[0] != '-')
														&& pfinfo->spec == 'd')
	{
		ft_insrt_to_str(&str, (pfinfo->flags & INV) ? " " : "+");
		str[0] = ((pfinfo->flags & POS)) ? '+' : str[0];
	}
	ft_prec_nums(pfinfo, &str);
	ft_pad_handle(pfinfo, &str);
	ft_dstr_append(dstr, str);
	free(str);
}

void		ft_octal_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	uintmax_t	oct;
	char		*str;

	if (pfinfo->spec == 'O')
		pfinfo->length = l;
	oct = ft_xou_len(pfinfo->length, ap);
	str = ft_uimaxtoa_base(oct, 8, "01234567");
	ft_handle_xou(&str, pfinfo);
	ft_dstr_append(dstr, str);
	free(str);
}

void		ft_hex_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	uintmax_t	hex;
	char		*str;

	if (pfinfo->spec == 'p')
		pfinfo->length = j;
	hex = ft_xou_len(pfinfo->length, ap);
	str = ft_uimaxtoa_base(hex, 16, "0123456789abcdef");
	if (pfinfo->spec == 'p' && pfinfo->flags & ZER && pfinfo->pset)
		pfinfo->flags ^= ZER;
	ft_handle_xou(&str, pfinfo);
	ft_dstr_append(dstr, str);
	free(str);
}

void		ft_uns_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	uintmax_t	uns;
	char		*str;

	if (pfinfo->spec == 'U')
		pfinfo->length = l;
	uns = ft_xou_len(pfinfo->length, ap);
	str = ft_uimaxtoa_base(uns, 10, "0123456789");
	ft_handle_xou(&str, pfinfo);
	ft_dstr_append(dstr, str);
	free(str);
}
