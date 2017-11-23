/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:58:10 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:44:25 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		echo_env(char *str, t_darr *newenvp)
{
	char *ret;

	if ((ret = msh_get_env(newenvp, str + 1)) != NULL)
	{
		ft_putstr(ret);
	}
	return (0);
}

int		echo_home(char *str, t_darr *newenvp)
{
	char *home;

	home = msh_get_env(newenvp, "HOME");
	if (home)
	{
		ft_putstr(home);
		if (str[1])
			ft_putstr(str + 1);
	}
	else
		ft_putstr(str);
	return (0);
}

int		echo_putstr(char *str, t_darr *newenvp)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (echo_env(&str[i], newenvp));
		else if (str[i] == '~')
			return (echo_home(&str[i], newenvp));
		else if (str[i] == '\\' && str[i + 1] == 'c')
			return (1);
		else if (str[i] == '\\')
			echo_esc_chr(str[i + 1]);
		else
		{
			write(1, &str[i], 1);
			++i;
			continue ;
		}
		i += 2;
	}
	return (0);
}

void	echo_print_args(char **args, t_darr *newenvp, int *i, int *put_nl)
{
	if (args[*i])
		if (echo_putstr(args[(*i)++], newenvp))
			*put_nl = 0;
	while (args[*i])
	{
		ft_putchar(' ');
		if (echo_putstr(args[(*i)++], newenvp))
			*put_nl = 0;
	}
}

int		msh_echo(char **args, t_darr *newenvp)
{
	int i;
	int nflag;
	int put_nl;

	i = 1;
	put_nl = 1;
	if (!args[1])
		ft_putchar('\n');
	if (!args[1])
		return (1);
	if ((nflag = !ft_strncmp("-n", args[1], 2)))
		++i;
	if (nflag)
		put_nl = 0;
	echo_print_args(args, newenvp, &i, &put_nl);
	if (put_nl)
		ft_putchar('\n');
	else if (i > 2)
		ft_printf("%{b_white}%{bblack}%%%{eoc}\n");
	return (1);
}
