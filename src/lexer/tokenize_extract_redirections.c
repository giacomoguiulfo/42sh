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

static void	get_suffix_word(char *instr, t_toke *help, t_tokelist *node)
{
	int len;

	len = 0;
	node->redir_suffix_file = instr + help->x;
	while (ft_isfilename(instr[++help->x]))
		len++;
	node->redir_suffix_len = len + 1;
}

static void	get_suffix_quote(char *instr, t_toke *help, t_tokelist *node)
{
	int		len;
	char	quote;

	len = 0;
	quote = instr[help->x];
	node->redir_suffix_file = instr + help->x + 1;
	quote = instr[help->x];
	while (instr[++help->x] != quote)
		len++;
	node->redir_suffix_len = len;
}

static void	get_suffix(char *instr, t_toke *help, t_tokelist *node)
{
	ft_printf("Found suffix: %s\n", instr + help->x);
	if (instr[help->x + 1] == '&' && ft_isdigit(instr[help->x + 2]))
	{
		//node->type[0] = '&';
		node->redir_suffix_fd = ft_atoi(instr + help->x + 2);
		help->x += 1;
		while (ft_isdigit(instr[++help->x]))
			;
		ft_printf("after redir %s\n", instr + help->x);
		return ;
	}
	while (instr[++help->x])
	{
		if (ft_isfilename(instr[help->x]))
		{
			get_suffix_word(instr, help, node);
			break ;
		}
		else if (ft_isquote(instr[help->x]))
		{
			get_suffix_quote(instr, help, node);
			break ;
		}
	}
}

void	extract_redirections(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = instr[help->x];
	if (instr[help->x] == instr[help->x + 1])
	{
		tmp->type[1] = instr[help->x + 1];
		help->x++;
	}
	get_prefix(instr, help, tmp);
	get_suffix(instr, help, tmp);
}
