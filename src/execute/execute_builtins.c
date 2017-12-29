/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"

int		aget_binary_size(char *bin)
{
	int x;

	x = -1;
	while (bin[++x] && ft_isalnum(bin[x]))
		;
	return (x);
}

bool	check_builtin(char *binary)
{
	bool	found;

	found = false;
	if ((ft_strncmp(binary, "cd", 2)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "exit", 4)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "env", 3)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "history", 7)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "setenv", 6)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "unsetenv", 8)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "exit", 4)) == 0)
		found = true;
	return (found);
}

int		msh_run_builtin(t_asttoken *this, char **env)
{
	int		ret;

	ret = 0;
	if ((ft_strcmp(this->binary, "cd")) == 0)
		ret = builtin_cd(this->args, env);
	else if ((ft_strcmp(this->binary, "exit")) == 0)
		ret = builtin_exit();
	else if ((ft_strcmp(this->binary, "env")) == 0)
		ret = builtin_exit();
	else if ((ft_strcmp(this->binary, "history")) == 0)
		ret = builtin_history();
	else if ((ft_strcmp(this->binary, "echo")) == 0)
		ret = builtin_echo(this->args, env);
	else if ((ft_strcmp(this->binary, "setenv")) == 0)
		ret = builtin_setenv(this->args, env);
	else if ((ft_strcmp(this->binary, "unsetenv")) == 0)
		ret = builtin_unsetenv(this->args, env);
	return (ret);
}
