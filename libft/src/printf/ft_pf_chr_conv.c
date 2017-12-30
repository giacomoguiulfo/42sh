/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_chr_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:34:08 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:43:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

void	ft_unicode_conv(wchar_t chr, char *str)
{
	if (chr < (MB_CUR_MAX == 1 ? 0xFF : 0x7F))
		str[0] = (unsigned char)chr;
	else if (chr < (1 << 11))
	{
		str[0] = (unsigned char)((chr >> 6) | 0xC0);
		str[1] = (unsigned char)((chr & 0x3F) | 0x80);
	}
	else if (chr < (1 << 16))
	{
		str[0] = (unsigned char)(((chr >> 12)) | 0xE0);
		str[1] = (unsigned char)(((chr >> 6) & 0x3F) | 0x80);
		str[2] = (unsigned char)((chr & 0x3F) | 0x80);
	}
	else if (chr < (1 << 21))
	{
		str[0] = (unsigned char)(((chr >> 18)) | 0xF0);
		str[1] = (unsigned char)(((chr >> 12) & 0x3F) | 0x80);
		str[2] = (unsigned char)(((chr >> 6) & 0x3F) | 0x80);
		str[3] = (unsigned char)((chr & 0x3F) | 0x80);
	}
}

int		ft_unicode_b(wchar_t chr)
{
	if (chr < (1 << 7))
		return (1);
	else if (chr < (1 << 11))
		return (2);
	else if (chr < (1 << 16))
		return (3);
	else if (chr < (1 << 21))
		return (4);
	return (0);
}

int		ft_handle_wchar(char **str, va_list ap)
{
	wchar_t	chr;
	int		len;

	chr = va_arg(ap, wchar_t);
	len = ft_unicode_b(chr);
	*str = ft_strnew(len);
	ft_unicode_conv(chr, *str);
	return (chr == '\0');
}

void	ft_null_chr(t_dstr *dstr, char *str)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(str);
	while (++i < len)
		if (str[i] == 1)
			str[i] = 0;
	ft_dstr_nappend(dstr, str, len);
}

void	ft_chr_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	char	chr;
	char	*str;
	int		null;

	if (pfinfo->spec == 'C' || pfinfo->length == l)
	{
		null = ft_handle_wchar(&str, ap);
		if (null)
			str[0] = null;
	}
	else
	{
		chr = va_arg(ap, int);
		str = ft_strnew(1);
		null = (chr == '\0') ? 1 : 0;
		str[0] = chr + null;
	}
	ft_pad_handle(pfinfo, &str);
	if (null)
		ft_null_chr(dstr, str);
	else
		ft_dstr_append(dstr, str);
	free(str);
}
