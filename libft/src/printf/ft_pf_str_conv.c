/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_str_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 17:33:03 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:16:30 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

char	*ft_null_str(t_info *pfinfo)
{
	char *temp;

	if (pfinfo->prec >= 1 || pfinfo->prec == -1)
	{
		temp = ft_strdup("(null)");
		if (pfinfo->prec > 6)
			temp[6] = '\0';
		else
			temp[(pfinfo->prec == -1) ? 6 : pfinfo->prec] = '\0';
	}
	else
		temp = ft_strdup("");
	return (temp);
}

void	ft_str_conv(t_dstr *dstr, t_info *pfinfo, va_list ap)
{
	char *ctemp;
	char *str;

	if (pfinfo->length == l)
	{
		ft_wstr_conv(dstr, pfinfo, ap);
		return ;
	}
	ctemp = va_arg(ap, char *);
	if (!ctemp)
		str = ft_null_str(pfinfo);
	else
		str = ft_strdup(ctemp);
	ft_prec_handle(pfinfo, &str);
	ft_pad_handle(pfinfo, &str);
	ft_dstr_append(dstr, str);
	free(str);
}
