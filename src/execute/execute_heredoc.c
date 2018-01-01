/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "history.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	cleanup(t_tokelist *redir, char buff[4092])
{
	history_add(buff);
	pipe(redir->heredoc);
	ft_dprintf(redir->heredoc[1], "%s", buff);
	close(redir->heredoc[1]);
	dup2(redir->heredoc[0], 0);
	close(redir->heredoc[0]);
}

static void	startup(t_tokelist *redir, t_here *doc)
{
	if (!redir->redir_suffix_file)
	{
		ft_printf("Kash: parse error near %s\n", redir->content);
		return ;
	}
	doc->prompt = ft_hstrdup("heredoc> ");
	doc->safe_word = ft_hstrdup("safe");
	ft_bzero((void*)doc->buff, 4092);
}

static bool	check_heredoc_exit(t_here *doc, char *redir_suffix_file)
{
	if (ft_strstr(doc->new_instr, redir_suffix_file))
	{
		return (true);
	}
	else if (ft_strstr(doc->new_instr, doc->safe_word))
	{
		ft_printf("You just used your safeword\n");
		return (true);
	}
	return (false);
}

static bool	check_heredoc_delim(t_tokelist *redir)
{
	t_here	doc;

	if (redir->redir_suffix_file)
	{
		ft_printf("Suffix file: %s\n");
		return (true);
	}
	ft_printf("Kash: please enter a delimiter character or phrase\n");
	ft_printf("Or, alternatively, you could just press enter and\n");
	ft_printf("we'll forget all about this heredoc business.\n");
	doc.new_instr = readline("delimter> ");
	if (!doc.new_instr)
		return (false);
	redir->redir_suffix_file = ft_hstrdup(doc.new_instr);
	free(doc.new_instr);
	return (true);
}

void		redirect_heredoc(t_tokelist *redir)
{
	t_here	doc;

	if (!check_heredoc_delim(redir))
		return ;
	startup(redir, &doc);
	while (42)
	{
		if (!(doc.new_instr = readline(doc.prompt)))
			continue ;
		else if (check_heredoc_exit(&doc, redir->redir_suffix_file))
			break ;
		ft_strcat(doc.buff, doc.new_instr);
		ft_strcat(doc.buff, "\n");
		free(doc.new_instr);
	}
	if (doc.new_instr)
		free(doc.new_instr);
	if (doc.buff[0] != 0)
		cleanup(redir, doc.buff);
}
