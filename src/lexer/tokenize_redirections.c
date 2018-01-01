/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_extract_redirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	check_redir_source(char *instr, t_toke *help, t_tokelist *node)
{
	int x;

	x = help->x;
	while (--x > 0 && ft_isdigit(instr[x]))
		;
	if (instr[x] == ' ' || ft_isdigit(instr[x]))
		node->redir_prefix_fd = ft_atoi(instr + x);
}

static void	get_prefix(char *instr, t_toke *help, t_tokelist *node)
{
	if (node->type[0] == '>')
	{
		if (help->x > 0 && instr[help->x - 1] == '&')
			node->redir_prefix_fd = -1;
		else if (help->x > 0 && ft_isdigit(instr[help->x - 1]))
			check_redir_source(instr, help, node);
	}
}

static void	get_fd(char *instr, t_toke *help, t_tokelist *node)
{
	if (ft_isdigit(instr[help->x + 2]))
	{
		node->redir_suffix_fd = ft_atoi(instr + help->x + 2);
		help->x += 1;
		while (ft_isdigit(instr[++help->x]))
			;
	}
	else if (instr[help->x + 2] == '-')
	{
		node->redir_turn_off = true;
		help->x += 2;
	}
}

static void	get_suffix(char *instr, t_toke *help, t_tokelist *node)
{
	ft_printf("suffix: %s\n", instr + help->x);
	if (instr[help->x + 1] == '&' && (ft_isdigit(instr[help->x + 2]) ||
		(instr[help->x + 1] == '&' && instr[help->x + 2] == '-')))
	{
		get_fd(instr, help, node);
		return ;
	}
	while (instr[++help->x])
	{
		if (get_file(instr, help, node))
			break ;
	}
}

void		tokenize_redirs(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = instr[help->x];
	tmp->content = instr + help->x;
	if (instr[help->x + 1] == tmp->type[0])
	{
		tmp->type[1] = instr[help->x + 1];
		help->x++;
	}
	get_prefix(instr, help, tmp);
	get_suffix(instr, help, tmp);
}
