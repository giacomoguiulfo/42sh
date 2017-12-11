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

/*typedef struct			s_asttoken
{
	char				*binary;
	char				**args;
	struct s_tokelist	**redirs;
	struct s_tokelist	*chain;
}						t_asttoken;

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

typedef struct			s_astree
{
	struct s_asttoken	*this;
	struct s_asttoken	*left;
	struct s_asttoken	*right;	
}						t_astree;

t_astree	*make_tree(t_asttoken **raw_materials)
{
	int			x;
	//t_astree	*mana;

	x = -1;
	ft_printf("\nStarting make_tree\n");
	while (raw_materials[++x])
	{
		if (raw_materials[x]->chain && raw_materials[x]->chain->type[0] == '&')
			ft_putstr("you found a dependent chain\n");
		else if (raw_materials[x]->chain && raw_materials[x]->chain->type[0] == '|' && raw_materials[x]->chain->type[1] == '|')
		{
			ft_putstr("you found a dependent chain\n");
			x++;
		}
		else if (raw_materials[x]->chain)
			ft_printf("You found a chain of variety %s\n", raw_materials[x]->chain->type);
	}
	ft_printf("\nFinished going through token list\n");
	return (NULL);
}

bool	parser(t_tokelist *tokens)
{
	t_asttoken	**pre_ast;
	t_astree	*mana;

	print_toke_list(tokens);
	pre_ast = synthesize_tokens(tokens);
	mana = make_tree(pre_ast);
	ft_heap_clear();
	return (true);
}
