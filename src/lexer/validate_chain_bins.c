/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chain_bins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/24 17:01:24 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

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
}

bool	check_binary(char *binary, char *path, int *x)
{
	char	bin_name[MAX_PATH_BIN_SIZE];
	char	valid_path[MAX_PATH_BIN_SIZE];
	char	*ptr;
	int		end;

	end = get_binary_size(binary);
	*x = *x + end;
	ptr = valid_path;
	ft_bzero(bin_name, MAX_PATH_BIN_SIZE);
	ft_strncpy(bin_name, binary, end);
	if (try_paths(bin_name, path, ptr))
		return (true);
	else if (try_pwd(binary))
		return (true);
	ft_printf("Lexer: command not found: %s\n", binary);
	return (false);
}

int		change_state(char *instr, int *x, int state)
{
	if ((instr[*x] == '|' && instr[*x + 1] == '|') ||
		(instr[*x] == '&' && instr[*x + 1] == '&'))
	{
		*x = *x + 1;
		if (state == 0)
		{
			ft_printf("Lexer: parse error near %c\n", instr[*x - 1]);
			return (false);
		}
	}
	else if (instr[*x] == '|')
	{
		if (state == 0)
			return (false);
	}
	return (true);
}

bool	check_builtin(char *binary, int *x)
{
	int 	end;
	bool	found;

	found = false;
	end = get_binary_size(binary);
	if ((ft_strncmp(binary, "cd", 2)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "exit", 4)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "env", 3)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "export", 3)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "history", 7)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "local", 5)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "setenv", 6)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "unset", 5)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "unsetenv", 8)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "exit", 4)) == 0)
		found = true;
	if (found == true)
		*x = *x + end;
	return (found);
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
			if (!check_builtin(instr + x, &x) && !check_binary(instr + x, path, &x))
				return (false);
			else
				state++;
		}
		else if (ft_ischain(instr + x))
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
