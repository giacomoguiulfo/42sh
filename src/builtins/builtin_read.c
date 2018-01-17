/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:55:46 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/17 14:45:43 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_sh.h"
#include <termios.h>

static t_optsdata	g_readopts =
{
	"read", NULL, NULL, NULL, 0, true, 0, {
		{'r', NULL, NULL, NULL, NULL, READ_OPT_LR, 0, NULL, 0, 0},
		{'u', NULL, NULL, NULL, NULL, READ_OPT_LU, 0, NULL, true, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};	

static int			read_assign(t_read *data, char **av)
{
	char	*ifs;
	char	*input;
	char	*token;
	char	**vars;

	ifs = ft_getenv(sh_singleton()->localenv, "IFS");
	vars = (*av) ? av : (char *[]){"REPLY", NULL};
	input = ((t_dstr)data->input).data;
	if (!vars[1])
		ifs = "\0";
	while (*vars)
	{
		token = ft_strsep(&input, ifs);
		builtin_setenv((char*[]){"local", *vars, token, NULL});
		vars++;
	}
	return (0);
}

static int			read_loop(t_read *data)
{
	int		ret;
	int		esc;
	char	buf[2];

	esc = 0;
	while (42)
	{
		if ((ret = read(data->fd, buf, 5) <= 0))
			return (ret);
		if (ret > 1)
			continue ;
		buf[1] = '\0';
		if (ft_isprint(*buf) || ft_isspace(*buf) || *buf == '\b')
		{
			if (buf[0] != data->delim)
				ft_dstr_append(&data->input, (char *)buf);
			ft_putchar(*buf);
		}
		if (buf[0] == 4 || (!esc && buf[0] == data->delim))
			break ;
		if (!READ_HAS_OPT_LR(data->optparser.flags))
			esc = esc ? 0 : (*buf == '\\');
	}
	return (0);
}

int					builtin_read(char **av)
{
	t_read	data;
	int		ret;

	ret = 0;
	data.optparser.flags = 0;
	if (ft_opts((char **)av, &g_readopts, &data, true))
		return (1);
	data.fd = 0;
	data.delim = '\n';
	ft_dstr_new(&data.input, 24);
	ret = read_loop(&data);
	if (!ret)
		read_assign(&data, data.optparser.argv);
	ft_dstr_free(&data.input);
	return (ret);
}
