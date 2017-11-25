/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:14:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/25 04:26:29 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <unistd.h>

#define CD_OPT_L (1 << 0)
#define CD_OPT_P (1 << 1)
#define CD_HAS_OPT_L(x) (x & CD_OPT_L)
#define CD_HAS_OPT_P(x) (x & CD_OPT_P)

static t_ftopts g_cdopts[] =
{
	{'L', NULL, CD_OPT_L, CD_OPT_P, NULL, 0},
	{'P', NULL, CD_OPT_P, CD_OPT_L, NULL, 0},
	{0, NULL, 0, 0, NULL, 0}
};

static int	ft_cd(char *operand, int flags)
{
	struct stat sb;
	char *linkname;

	int ret;
	lstat(operand, &sb);
	if (CD_HAS_OPT_P(flags) && S_ISLNK(sb.st_mode))
	{
		linkname = ft_memalloc(sb.st_size + 1);
		ret = readlink(operand, linkname, sb.st_size + 1);
		ret = chdir(linkname);
		// TODO: Set oldpwd and pwd based on linkname
		ft_strdel(&linkname);
	}
	ret = chdir(operand);
	DEBUG("%d", ret);
	return (0);
}

static char *cd_operand(char *arg)
{
	if (arg)
	{
		if (!ft_strcmp(arg, "-"))
			return (ft_strdup(ft_getenv(shell_singleton()->env, "OLDPWD")));
		return (ft_strdup(arg));
	}
	return (ft_strdup(ft_getenv(shell_singleton()->env, "HOME")));
}

int builtin_cd(char **av, char **envp __attribute((unused)))
{
	t_ftopts_data	data;
	char			*operand;
	char			*oldpwd;

	if (ft_getopts(av, g_cdopts, &data))
		return (1);
	operand = cd_operand(data.argv[0]);
	oldpwd = getcwd(NULL, 0);
	if (operand)
		ft_cd(operand, data.flags);
		//return chdir(operand);
	ft_strdel(&operand);
	ft_strdel(&oldpwd);
	return (0);
}
