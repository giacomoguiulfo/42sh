/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chain_bins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int		get_binary_size(char *bin)
{
	int x;

	x = -1;
	while (bin[++x] && ft_isalnum(bin[x]))
		;
	return (x);
}

bool	try_paths(char *binary, char *path, char *try_this_path)
{
	struct stat sb;
	char		*start;
	char		*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, 4096);
		ft_strncpy(try_this_path, start, end - start);
		ft_strcat(try_this_path, "/");
		ft_strcat(try_this_path, binary);
		if ((lstat(try_this_path, &sb)) != -1)
		{
			if (!check_access(binary, try_this_path))
				return (false);
			else if (!check_reg_file(sb.st_mode, binary))
				return (false);
			return (true);
		}
		start = end + 1;
	}
	return (false);
}

bool	check_binary(char *binary, char *path, int *x)
{
	char	bin_name[4096];
	char	valid_path[4096];
	char	*ptr;
	int		end;

	end = get_binary_size(binary);
	*x = *x + end;
	ptr = valid_path;
	ft_bzero(bin_name, 4096);
	ft_strncpy(bin_name, binary, end);
	if (try_paths(bin_name, path, ptr))
		return (true);
	return (false);
}

int		change_state(char *instr, int *x, int state)
{
	if (instr[*x] == '|' && instr[*x + 1] == '|' && (*x = *x + 1))
	{
		if (state == 0)
			return (false);
	}
	else if (instr[*x] == '|')
	{
		if (state == 0)
			return (false);
	}
	else if (instr[*x] == '&' && instr[*x + 1] == '&' && (*x = *x + 1))
	{
		if (state == 0)
			return (false);
	}
	return (true);
}

bool	validate_chain_bins(char *instr)
{
	char	*path;
	int		x;
	int		state;

	x = -1;
	state = 0;
	path = get_path();
	while (instr[++x])
	{
		if (ft_isalnum(instr[x]) && state == 0)
		{
			if (!check_binary(instr + x, path, &x))
				return (false);
			else
				state++;
		}
		else if (instr[x] == '|' || instr[x] == '&')
		{
			if (!change_state(instr + x, &x, state))
				return (false);
			state = 0;
		}
	}
	if (state == 0)
		return (false);
	return (true);
}
