/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:55:46 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/17 17:29:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_sh.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <termios.h>

static int	read_get_fd(char *def, char *fd, t_read *data)
{
	(void)def;
	if (!data)
		return (1);
	data->fd = ft_atoi(fd);
	return (0);
}

static t_optsdata	g_readopts =
{
	"read", NULL, NULL, NULL, 0, true, 0, {
		{'r', NULL, NULL, NULL, NULL, READ_OPT_LR, 0, NULL, 0, 0},
		{'u', NULL, NULL, NULL, NULL, READ_OPT_LU, 0, &read_get_fd, true, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

static int	read_assign(t_read *data, char **av)
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
		if (builtin_setenv((char*[]){"local", *vars, token, NULL}))
			return (1);
		vars++;
	}
	return (0);
}

static int	read_loop(t_read *data)
{
	int		ret;
	int		esc;
	char	buf[4];

	esc = 0;
	while (42)
	{
		if ((ret = read(data->fd, buf, 4) <= 0))
			return (ret);
		buf[1] = '\0';
		ft_putchar(*buf);
		if (*buf == 4 || (!esc && *buf == data->delim))
			break ;
		if (!READ_HAS_OPT_LR(data->optparser.flags))
			esc = esc ? 0 : (*buf == '\\');
		ft_dstr_append(&data->input, buf);
	}
	return (0);
}

static int	read_init(t_read *data, char **av)
{
	struct termios term;

	data->fd = STDIN;
	data->delim = '\n';
	data->optparser.flags = 0;
	if (ft_dstr_new(&data->input, 24))
		return (1);
	if (isatty(STDIN))
	{
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		term.c_cc[VEOL] = data->delim;
		if (tcsetattr(STDIN, TCSANOW, &term) == -1)
		{
			SH_ERR2("tcsetattr: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	if (ft_opts(av, &g_readopts, data, true))
		return (1);
	return (0);
}

int			builtin_read(char **av)
{
	t_read	data;

	if (read_init(&data, av))
		return (1);
	if (read_loop(&data))
		return (1);
	if (read_assign(&data, data.optparser.argv))
		return (1);
	ft_dstr_free(&data.input);
	return (0);
}
