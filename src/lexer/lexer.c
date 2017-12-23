/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "lexer.h"
#include "libft.h"
#include "history.h"
#include <stdlib.h>

/*static int		get_binary_size(char *bin)
{
	int x;

	x = -1;
	while (bin[++x] && ft_isalnum(bin[x]))
		;
	return (x);
}*/
/*
bool	try_paths(char *binary, char *path, char *try_this_path)
{
	struct stat sb;
	char		*start;
	char		*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, MAX_PATH_BIN_SIZE);
		ft_strncpy(try_this_path, start, end - start);
		ft_strcat(try_this_path, "/");
		ft_strcat(try_this_path, binary);
		if ((lstat(try_this_path, &sb)) != -1)
		{
			if (!check_access(binary, try_this_path))
				return (false);
			else if (!check_reg_file(sb.st_mode))
				return (false);
			return (true);
		}
		start = end + 1;
	}
	return (false);
}*/

int		validate_quotes_chains(char **instr)
{
	int valid;

	valid = 0;
	if (!validate_quotes(*instr))
	{
		quote_prompt(instr, "quotes> ");
		return (valid);
	}
	else if ((valid = validate_chains(*instr)) == 0)
	{
		quote_prompt(instr, "chain> ");
		return (valid);
	}
	return (valid);
}

bool		validate(char **instr)
{
	int		valid;

	valid = 0;
	while (!valid)
	{
		valid = validate_quotes_chains(instr);
		if (valid == -1)
			return (false);
	}
	//if (!validate_chain_bins(*instr)) To do: validate right before command execution
	//	return (false);
	if (!validate_redirections(*instr))
		return (false);
	return (true);
}
			
t_tokelist	*lexer(char **instr)
{
	t_tokelist *abstract;

	if (!validate(instr))
	{
		ft_printf("Lexer: Not a valid command: %s\n", *instr);
		return (NULL);
	}
	abstract = tokenize(*instr);
	return (abstract);
}