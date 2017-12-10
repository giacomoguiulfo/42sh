/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
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

void		ft_putnstr(char *str, size_t len)
{
	write(1, str, len);
}

void		print_toke_list(t_tokelist *head)
{
	t_tokelist *tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("\n----------\n");
		ft_printf("type: %s\n", tmp->type);
		if (tmp->type[0] == '>' || tmp->type[0] == '<')
		{
			if (tmp->redir_suffix_fd != -2)
				ft_printf("Suffix_fd is %d\n", tmp->redir_suffix_fd);
			else if (tmp->redir_suffix_file)
			{
				ft_printf("Suffix file is: ");
				ft_putnstr(tmp->redir_suffix_file, tmp->redir_suffix_len);
				ft_putchar('\n');
			}
			else if (tmp->redir_prefix_fd != -2)
				ft_printf("Prefix_fd is %d\n", tmp->redir_prefix_fd);
		}
		if (ft_isquote(tmp->type[0]))
		{
			ft_printf("Quote text: ");
			ft_putnstr(tmp->content, tmp->len);
			ft_putchar('\n');
		}
		else if (tmp->type[0] == 'w')
		{
			ft_printf("Word text: ");
			ft_putnstr(tmp->content, tmp->len);
			ft_putchar('\n');
		}
		ft_printf("---------->\n");
		tmp = tmp->next;
	}
}

/*
typedef struct			s_tokelist
{
	void				*content;
	size_t				len;
	char				type[3];
	int					redir_prefix_fd;
	char				*redir_suffix_file;
	int					redir_suffix_len;
	int					redir_suffix_fd;
	struct s_tokelist	*next;
}						t_tokelist;*/

void		add_binary(t_asttoken *build, t_tokelist *binary)
{
	build->binary = ft_hstrndup(binary->content, binary->len);
	ft_printf("binary: %s\n", build->binary);
}

void		add_args(t_asttoken *build, t_tokelist *arg)
{
	add_astarg(build, arg);
	int x;

	x = 0;
	while (build->args[++x])
		ft_printf("Args %d: %s\n", x, build->args[x]);
}

void		add_chain(t_asttoken *build, t_tokelist *arg)
{
	build->chain = arg;
}

void		add_redir(t_asttoken *build, t_tokelist *arg)
{
	build->redir
}

t_asttoken	**synthesize_tokens(t_tokelist *tokens)
{
	t_tokelist	*tmp;
	t_asttoken	**build;
	int			count;

	tmp = tokens;
	build = start_asttoken();
	count = 0;
	while (tmp)
	{
		if (tmp->type[0] == 'w' || ft_isquote(tmp->type[0]))
		{
			if (!build[count])
				build[count] = add_asttoken(build);
			if (!build[count]->binary)
				add_binary(build[count], tmp);
			else
				add_args(build[count], tmp);

		}
		else if (tmp->type[0] == '>' || tmp->type[0] == '<')
		{
			add_redirection(build[x], tmp);
			ft_putstr("Found a redirection\n");
		}
		else if (ft_iscompletechain(tmp->type))
		{
			add_chain(build[count], tmp);
			count++;
		}
		tmp = tmp->next;
	}
	return (build);
}

bool	parser(t_tokelist *tokens)
{
	t_asttoken **pre_ast;

	print_toke_list(tokens);
	pre_ast = synthesize_tokens(tokens);
	return (true);
}