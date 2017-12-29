/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_synthesizer_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"

void		add_binary(t_asttoken *build, t_tokelist *binary)
{
	build->binary = ft_hstrndup(binary->content, binary->len);
	add_astarg(build, NULL);
}

void		add_args(t_asttoken *build, t_tokelist *arg)
{
	add_astarg(build, arg);
}

void		add_chain(t_asttoken *build, t_tokelist *arg)
{
	build->chain = arg->content;
}

void		add_redir(t_asttoken *build, t_tokelist *arg)
{
	add_astredir(build, arg);
}
