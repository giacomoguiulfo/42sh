/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 05:47:57 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:17:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

char g_colors[33][2][15] = {
	{"{red}", "\033[31m"},
	{"{bred}", "\033[31;1m"},
	{"{green}", "\033[32m"},
	{"{bgreen}", "\033[32;1m"},
	{"{yellow}", "\033[33m"},
	{"{byellow}", "\033[33;1m"},
	{"{blue}", "\033[34m"},
	{"{bblue}", "\033[34;1m"},
	{"{purple}", "\033[35m"},
	{"{bpurple}", "\033[35;1m"},
	{"{cyan}", "\033[36m"},
	{"{bcyan}", "\033[36;1m"},
	{"{black}", "\033[30m"},
	{"{bblack}", "\033[30;1m"},
	{"{white}", "\033[37m"},
	{"{bwhite}", "\033[37;1m"},
	{"{b_red}", "\033[41m"},
	{"{b_bred}", "\033[41;1m"},
	{"{b_green}", "\033[42m"},
	{"{b_bgreen}", "\033[42;1m"},
	{"{b_yellow}", "\033[43m"},
	{"{b_byellow}", "\033[43;1m"},
	{"{b_blue}", "\033[44m"},
	{"{b_bblue}", "\033[44;1m"},
	{"{b_purple}", "\033[45m"},
	{"{b_bpurple}", "\033[45;1m"},
	{"{b_cyan}", "\033[46m"},
	{"{b_bcyan}", "\033[46;1m"},
	{"{b_black}", "\033[40m"},
	{"{b_bblack}", "\033[40;1m"},
	{"{b_white}", "\033[47m"},
	{"{b_bwhite}", "\033[47;1m"},
	{"{eoc}", "\033[0m"}
};

bool		ft_pfcolors(t_dstr *dstr, const char **format)
{
	int	i;

	i = 0;
	while (i < 33)
	{
		if (ft_strncmp(*format, g_colors[i][0], ft_strlen(g_colors[i][0])) == 0)
		{
			ft_dstr_append(dstr, g_colors[i][1]);
			*format = *format + ft_strlen(g_colors[i][0]);
			return (true);
		}
		++i;
	}
	return (false);
}

void		ft_binary_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	uintmax_t	binary;
	char		*str;

	binary = va_arg(ap, unsigned long long);
	str = ft_uimaxtoa_base(binary, 2, "01");
	ft_handle_xou(&str, pfinfo);
	ft_dstr_append(dstr, str);
	free(str);
}

intmax_t	*ft_printf_n_len(t_info *pfinfo, va_list ap)
{
	if (pfinfo->length == hh)
		return ((intmax_t *)va_arg(ap, signed char *));
	if (pfinfo->length == h)
		return ((intmax_t *)va_arg(ap, short *));
	if (pfinfo->length == l)
		return ((intmax_t *)va_arg(ap, long *));
	if (pfinfo->length == ll)
		return ((intmax_t *)va_arg(ap, long long *));
	if (pfinfo->length == j)
		return ((intmax_t *)va_arg(ap, intmax_t *));
	if (pfinfo->length == z)
		return ((intmax_t *)va_arg(ap, ssize_t *));
	return ((intmax_t *)va_arg(ap, int *));
}

void		ft_none_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	intmax_t	*i;
	int			tmp;

	tmp = dstr->len;
	i = ft_printf_n_len(pfinfo, ap);
	*i = (intmax_t)tmp;
}
