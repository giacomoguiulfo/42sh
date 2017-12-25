/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:14:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/23 22:48:09 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <unistd.h>

#define CD_OPT_L 		(1 << 0)
#define CD_OPT_P 		(1 << 1)
#define CD_HAS_OPT_L(x) (x & CD_OPT_L)
#define CD_HAS_OPT_P(x) (x & CD_OPT_P)
#define CD_ERR_0		"cd: %s: No such file or directory"
#define CD_ERR_1		"cd: %s: Not a directory"
#define CD_ERR_2		"cd: %s: Permission denied"
#define CD_ERR_3		"cd: unable to proceed: %s"

static t_optsdata g_cdopts =
{
	"cd", NULL, NULL, NULL, 0, true, 0, {
		{'L', NULL, NULL, NULL, NULL, CD_OPT_L, CD_OPT_P, NULL, 0, 0},
		{'P', NULL, NULL, NULL, NULL, CD_OPT_P, CD_OPT_L, NULL, 0, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

static void cd_setpwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	builtin_setenv((char*[]){"cd", "PWD", cwd, NULL}, NULL);
	ft_strdel(&cwd);
}

static int	cd_symlink(char *operand, struct stat *sb)
{
	char *linkname;

	linkname = ft_memalloc(sb->st_size + 1);
	if (readlink(operand, linkname, sb->st_size + 1))
		return (SH_ERR(CD_ERR_3, operand));
	if (chdir(linkname))
	{
		ft_strdel(&linkname);
		return (SH_ERR(CD_ERR_3, operand));
	}
	cd_setpwd();
	ft_strdel(&linkname);
	return (0);
}

static int	cd_routine(char *operand, int flags)
{
	struct stat sb;

	if (access(operand, F_OK))
		return (SH_ERR(CD_ERR_0, operand));
	if (!ft_isdir(operand))
		return (SH_ERR(CD_ERR_1, operand));
	if (access(operand, X_OK) && lstat(operand, &sb))
		return (SH_ERR(CD_ERR_2, operand));
	if (CD_HAS_OPT_P(flags) && S_ISLNK(sb.st_mode))
		return (cd_symlink(operand, &sb));
	if (chdir(operand))
		return (SH_ERR(CD_ERR_3, operand));
	cd_setpwd();
	return (0);
}

static char *cd_operand(char *arg)
{
	if (arg)
	{
		if (!ft_strcmp(arg, "-"))
			return (ft_strdup(ft_getenv(sh_singleton()->env, "OLDPWD")));
		return (ft_strdup(arg));
	}
	return (ft_strdup(ft_getenv(sh_singleton()->env, "HOME")));
}

int builtin_cd(char **av, char **envp __attribute((unused)))
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
		builtin_setenv((char*[]){"setenv", "OLDPWD", oldpwd, NULL}, NULL);
		cd_setpwd();
	}
	else if ((ret = cd_routine(operand, data.flags)) == 0)
		builtin_setenv((char*[]){"setenv", "OLDPWD", oldpwd, NULL}, NULL);
	ft_strdel(&operand);
	ft_strdel(&oldpwd);
	return (ret);
}
