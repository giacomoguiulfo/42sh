/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

typedef struct			s_toke
{
	char				*start;
	char				*end;
	char				quote_type;
	int					x;
	int					state;
}						t_toke;

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
}						t_tokelist;

void	ft_putnstr(char *str, size_t len)
{
	write(1, str, len);
}

int		ft_iscompletechain(char *str)
{
	if (ft_ischain(str))
		return (1);
	else if (str[0] == ';')
		return (1);
	return (0);
}

t_tokelist *start_toking(void)
{
	t_tokelist *head;

	head = (t_tokelist*)ft_memalloc(sizeof(t_tokelist));
	head->content = NULL;
	head->next = NULL;
	head->len = 0;
	head->type[0] = '\0';
	head->type[1] = '\0';
	head->type[2] = '\0';
	head->redir_prefix_fd = -2;
	head->redir_suffix_fd = -2;
	head->redir_suffix_file = NULL;
	head->redir_suffix_len = -1;
	return (head);
}

t_tokelist	*tokenize_constructor(t_toke *help, char *instr)
{
	t_tokelist *head;

	help->start = instr;
	help->end = NULL;
	help->x = -1;
	help->state = 0;
	return ((head = start_toking()));
}

t_tokelist *add_toke(t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_tokelist*)ft_memalloc(sizeof(t_tokelist));
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->len = 0;
	tmp->type[0] = '\0';
	tmp->type[1] = '\0';
	tmp->type[2] = '\0';
	tmp->redir_prefix_fd = -2;
	tmp->redir_suffix_fd = -2;
	tmp->redir_suffix_file = NULL;
	tmp->redir_suffix_len = -2;
	return (tmp);
}

void	extract_quotes(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head->content)
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = instr[help->x];
	help->start = instr + help->x;
	while (instr[++help->x] && instr[help->x] != tmp->type[0])
		;
	help->end = instr + help->x;
	tmp->len = (help->end - 1) - (help->start);
	tmp->content = help->start + 1;
}

void	check_redir_source(char *instr, t_toke *help, t_tokelist *node)
{
	int x;

	x = help->x;
	ft_printf("Gathering int redirection source\n");
	while (--x > 0 && ft_isdigit(instr[x]))
		;
	if (instr[x] == ' ' || ft_isdigit(instr[x]))
		node->redir_prefix_fd = ft_atoi(instr + x);
}

void	get_prefix(char *instr, t_toke *help, t_tokelist *node)
{
	if (node->type[0] == '>')
	{
		if (help->x > 0 && instr[help->x - 1] == '&')
			node->redir_prefix_fd = -1;
		else if (help->x > 0 && ft_isdigit(instr[help->x - 1]))
			check_redir_source(instr, help, node);
	}
}

int		ft_isfilename(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '_' || c == '.' || c == ',' || c == '-' || c == '=' ||
		c == '+' || c == '%' || c == '#' || c == '@' || c == '^')
		return (1);
	return  (0);
}

void	get_suffix(char *instr, t_toke *help, t_tokelist *node)
{
	int len;
	char quote;

	len = 0;
	quote = 0;
	if (instr[help->x + 1] == '&' && ft_isdigit(instr[help->x + 2]))
	{
		node->type[0] = '&';
		node->redir_suffix_fd = ft_atoi(instr + help->x + 2);
		help->x += 1;
		return ;
	}
	while (instr[++help->x])
	{
		if (ft_isfilename(instr[help->x]))
		{
			node->redir_suffix_file = instr + help->x;
			while (ft_isfilename(instr[++help->x]))
				len++;
			node->redir_suffix_len = len + 1;
			break ;
		}
		else if (ft_isquote(instr[help->x]))
		{
			node->redir_suffix_file = instr + help->x + 1;
			quote = instr[help->x];
			while (instr[++help->x] != quote)
				len++;
			node->redir_suffix_len = len;
			break ;
		}
	}
}

void	extract_redirections(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	ft_printf("Starting redirection extraction\n");
	if (!head->content)
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
	ft_printf("Redirection type: %s\n", tmp->type);
	if (tmp->redir_prefix_fd != -2)
	{
		if (tmp->redir_prefix_fd == -1)
			ft_printf("Redirection fd prefix is &\n");
		else
			ft_printf("Redirection prefix fd: %d\n", tmp->redir_prefix_fd);
	}
	if (tmp->redir_suffix_fd != -2)
	{
		if (tmp->redir_suffix_fd != -2)
			ft_printf("Redirection suffix is & and fd is %d\n", tmp->redir_suffix_fd);
		else
			ft_printf("Redirection suffix file: %s\n", tmp->redir_suffix_file);
	}
	if (tmp->redir_suffix_file)
	{
		ft_printf("Redirection suffix file: ");
		ft_putnstr(tmp->redir_suffix_file, tmp->redir_suffix_len);
		ft_putchar('\n');
	}
	ft_printf("Ending redirection extraction\n");
}

void	get_chain_type(char *instr, t_toke *help, t_tokelist *node)
{
	if (instr[help->x] == '&' && instr[help->x + 1] == '&')
	{
		node->type[0] = '&';
		node->type[1] = '&';
	}
	else if (instr[help->x] == '|' && instr[help->x + 1] == '|')
	{
		node->type[0] = '|';
		node->type[1] = '|';
	}
	else if (instr[help->x] == '|')
		node->type[0] = '|';
	else if (instr[help->x] == ';')
		node->type[0] = ';';
}

void	extract_chain(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head->content)
		tmp = head;
	else
		tmp = add_toke(head);
	get_chain_type(instr, help, tmp);
	ft_printf("Chain type is %s\n", tmp->type);
}

void	tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;
	t_tokelist	*tmp;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	tmp = head;
	ft_printf("Instructions are: %s\n", instructions);
	while (instructions[++help.x])
	{
		if (ft_isquote(instructions[help.x]))
		{
			extract_quotes(instructions, &help, head);
			if (tmp->next)
				tmp = tmp->next;
			ft_printf("Quote type is %c\n", tmp->type[0]);
			ft_printf("Quote text is: ");
			ft_putnstr(tmp->content, tmp->len);
			ft_putchar('\n');
		}
		else if (instructions[help.x] == '>' || instructions[help.x] == '<')
		{
			extract_redirections(instructions, &help, head);
			if (tmp->next)
				tmp = tmp->next;
			ft_putnstr(tmp->content, tmp->len);
		}
		else if (ft_iscompletechain(instructions + help.x))
		{
			extract_chain(instructions, &help, head);
			if (tmp->next)
				tmp = tmp->next;
		}
		// else if ft_ischain(instructions[help.x]) // manage chains
		//else if ((ft_isquote(instructions[help.x])) || (ft_isalnum(instructions[help.x]))) manage binaries
	}
	ft_printf("Finished tokenizing\n");
}