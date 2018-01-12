/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:55:46 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/11 11:46:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <termios.h>

#define READ_OPT_LR (1 << 0)
#define READ_OPT_LU (1 << 0)
#define READ_HAS_OPT_LR(a) (a & READ_OPT_LR)
#define READ_HAS_OPT_LU(a) (a & READ_OPT_LU)

typedef struct	s_read
{
	t_optparser optparser;
	t_dstr		input;
	int			fd;
	char		delim;
}				t_read;

static int read_get_fd(char *u __attribute((unused)), char *fd, t_read *data)
{
	data->fd = ft_atoi(fd);
	return (0);
}

static t_optsdata g_readopts =
{
	"read", NULL, NULL, NULL, 0, true, 0, {
		{'r', NULL, NULL, NULL, NULL, READ_OPT_LR, 0, NULL, 0, 0},
		{'u', NULL, NULL, NULL, NULL, READ_OPT_LU, 0, read_get_fd, true, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

static int	read_assign(t_read *data)
{
	(void)data;
	return (0);
}

static int	read_loop(t_read *data)
{
	int		ret;
	int		esc;
	char	buf[2];

	esc = 0;
	while (42)
	{
		if ((ret = read(data->fd, buf, 5) <= 0))
			return (ret);
		if (*buf == '\b')
			DBG("It's a backspace");
		DBG("%d", *buf);
		if (ret > 1)
			continue ;
		buf[1] = '\0';
		if (buf[0] == 4)
			break ;
		if (ft_isprint(*buf) || ft_isspace(*buf) || *buf == '\b')
		{
			ft_dstr_append(&data->input, (char *)buf);
			ft_putchar(*buf);
		}
		if (!esc && buf[0] == data->delim)
			break ;
		if (!READ_HAS_OPT_LR(data->optparser.flags))
			esc = esc ? 0 : (*buf == '\\');
	}
	return (0);
}

void	read_settings(t_read *read)
{
	(void)read;
	struct termios term;

	tcgetattr(STDIN, &term);
	term.c_lflag |= (ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[0] = 0;
	tcsetattr(STDIN, TCSANOW, &term);
}

int	builtin_read(char *av[])
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
	read_settings(&data);
	ret = read_loop(&data);
	DBG("%s", ((t_dstr)data.input).data);
	if (!ret)
		ret = read_assign(&data);
	ft_dstr_free(&data.input);
	return (ret);
}
