/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:14:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/22 13:15:48 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#define CD_ENOENT		"cd: %s: No such file or directory"
#define CD_ENOTDIR		"cd: %s: Not a directory"
#define CD_EACCES		"cd: %s: Permission denied"
#define CD_EPERM		"cd: unable to proceed: %s"
#define CD_OPT_L		(1 << 0)
#define CD_OPT_P		(1 << 1)
#define CD_HAS_OPT_L(x)	(x & CD_OPT_L)
#define CD_HAS_OPT_P(x)	(x & CD_OPT_P)

static t_optsdata g_cdopts =
{
	"cd", NULL, NULL, NULL, 0, true, 0, {
		{'L', NULL, NULL, NULL, NULL, CD_OPT_L, CD_OPT_P, NULL, 0, 0},
		{'P', NULL, NULL, NULL, NULL, CD_OPT_P, CD_OPT_L, NULL, 0, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

/*
** Set PWD env variable value to cwd.
*/

static void	cd_setpwd(char *dir)
{
	char	*cwd;
	char	*pwd;

	pwd = NULL;
	cwd = getcwd(NULL, 0);
	if (dir)
		ft_asprintf(&pwd, "%.*s/%s", ft_strlenrchr(cwd, '/'), cwd, dir);
	builtin_setenv((char*[]){"cd", "PWD", (dir) ? pwd : cwd, NULL});
	ft_strdel(&cwd);
	ft_strdel(&pwd);
}

/*
** Perform CD routine
**
** @operand:
** @sb:
** @return:		0 when success, non-zero if there is an error.
*/

static int	cd_symlink(char *operand)
{
	char		linkname[PATH_MAX + 1];
	ssize_t	ret;

	if ((ret = readlink(operand, linkname, PATH_MAX + 1)) == -1)
		return (SH_ERR2_R1(CD_EPERM, operand));
	linkname[ret] = '\0';
	if (chdir(linkname))
		return (SH_ERR2_R1(CD_EPERM, operand));
	cd_setpwd(operand);
	return (0);
}

static int	cd_routine(char *operand, int flags)
{
	struct stat sb;

	if (access(operand, F_OK))
		return (SH_ERR2_R1(CD_ENOENT, operand));
	if (!ft_isdir(operand))
		return (SH_ERR2_R1(CD_ENOTDIR, operand));
	if (access(operand, X_OK))
		return (SH_ERR2_R1(CD_EACCES, operand));
	if (lstat(operand, &sb))
		return (SH_ERR2_R1(CD_EACCES, operand));
	if (CD_HAS_OPT_P(flags) && S_ISLNK(sb.st_mode))
		return (cd_symlink(operand));
	if (chdir(operand))
		return (SH_ERR2_R1(CD_EPERM, operand));
	cd_setpwd(NULL);
	return (0);
}


static char	*cd_operand(char *arg)
{
	if (arg)
	{
		if (!ft_strcmp(arg, "-"))
			return (ft_strdup(ft_getenv(sh_singleton()->env, "OLDPWD")));
		return (ft_strdup(arg));
	}
	return (ft_strdup(ft_getenv(sh_singleton()->env, "HOME")));
}

int			builtin_cd(char **av)
{
	t_optparser	data;
	char		*operand;
	char		*oldpwd;
	int			ret;

	data.flags = 0;
	if (ft_opts(av, &g_cdopts, &data, true))
		return (1);
	operand = cd_operand(data.argv[0]);
	oldpwd = getcwd(NULL, 0);
	ret = 0;
	if (!operand)
	{
		builtin_setenv((char*[]){"setenv", "OLDPWD", oldpwd, NULL});
		cd_setpwd(NULL);
	}
	else if ((ret = cd_routine(operand, data.flags)) == 0)
		builtin_setenv((char*[]){"setenv", "OLDPWD", oldpwd, NULL});
	ft_strdel(&operand);
	ft_strdel(&oldpwd);
	return (ret);
}
