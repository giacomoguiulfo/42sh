/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 01:01:46 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/23 21:23:43 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"

void	ft_opts_parse(t_optsdata *optsdata, void *data)
{
	((t_optparser *)data)->argv = optsdata->argv;
}
