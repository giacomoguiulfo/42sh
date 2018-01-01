/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts_suggest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 21:22:29 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/23 21:22:51 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"
#include "libft.h"

int			ft_opts_suggest(t_optsdata *optsdata)
{
	ft_dprintf(STDERR_FILENO, "Try '%s --help' for more information\n",
	optsdata->prog);
	return (0);
}
