/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/25 18:23:21 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"
#include <stdlib.h>

bool		get_find_info(t_sub *this, char *find, char letter)
{
	if (!(this->start = ft_strchr(find, letter)))
		return (false);
	this->start++;
	this->x = -1;
	while (ft_isfilename(this->start[++this->x]))
		;
	this->end = this->start + this->x;
	if (this->x == 0)
		return (false);
	return (true);
}

char		*make_sub(char *find, t_sub *help, t_sub *more)
{
	char	buff[4092];

	ft_bzero((void*)buff, 4092);
	ft_strncpy(buff, find - 1, help->start - find);
	ft_strcat(buff, more->end + 1);
	ft_strcat(buff, help->end);
	return (ft_hstrdup(buff));
}

void		check_for_env(char **find, char this)
{
	char	**env;
	int		x;
	t_sub	help;
	t_sub	more;

	if (!(get_find_info(&help, *find, this)))
		return ;
	env = (sh_singleton())->env;
	x = -1;
	while (env[++x])
	{
		if (!(more.end = ft_strchr(env[x], '=')))
			continue ;
		more.start = env[x];
		if ((ft_strncmp(more.start, help.start, help.x)) != 0)
			continue ;
		*find = make_sub(*find, &help, &more);
	}
}

void		check_for_home(char **find, char this)
{
	char	*found;
	char	*path;
	char	buff[4092];

	if (!(found = ft_strchr(*find, this)))
		return ;
	else if (!(found + 1))
		return ;
	path = get_home();
	path = ft_strchr(path, '=');
	path++;
	ft_bzero((void*)buff, 4092);
	ft_strncpy(buff, *find, found - *find);
	ft_strcat(buff, path);
	ft_strcat(buff, found + 1);
	*find = ft_hstrdup(buff);
}

void		substitution_requests(t_asttoken **pre_ast)
{
	int x;
	int y;

	x = -1;
	while (pre_ast[++x])
	{
		if (pre_ast[x]->binary && pre_ast[x]->args[0])
		{
			check_for_env(&pre_ast[x]->binary, '$');
			check_for_home(&pre_ast[x]->binary, '~');
			y = -1;
			while (pre_ast[x]->args[++y])
			{
				check_for_env(&pre_ast[x]->args[y], '$');
				check_for_home(&pre_ast[x]->args[y], '~');
			}
		}
	}
}
