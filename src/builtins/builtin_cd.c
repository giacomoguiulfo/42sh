/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:14:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 01:44:20 by giacomo          ###   ########.fr       */
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

int	file_is_dir(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb))
		return (0);
	return (S_ISDIR(sb.st_mode));
}

static void cd_setpwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	builtin_setenv(NULL, (char*[]){"cd", "PWD", cwd, NULL}, NULL);
	ft_strdel(&cwd);
}

static int	cd_symlink(char *operand, struct stat *sb)
{
	char *linkname;

	linkname = ft_memalloc(sb->st_size + 1);
	if (readlink(operand, linkname, sb->st_size + 1))
		return (1);
	if (chdir(linkname))
	{
		ft_strdel(&linkname);
		return (1);
	}
	cd_setpwd();
	ft_strdel(&linkname);
	return (0);
}

static int	ft_cd(char *operand, int flags)
{
	struct stat sb;

	if (access(operand, F_OK))
		return (1);
	if (!file_is_dir(operand))
		return (1);
	if (access(operand, X_OK) && lstat(operand, &sb))
		return (1);
	if (CD_HAS_OPT_P(flags) && S_ISLNK(sb.st_mode))
		return (cd_symlink(operand, &sb));
	if (chdir(operand))
		return (1);
	cd_setpwd();
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
	int				ret;

	if (ft_getopts(av, g_cdopts, &data))
		return (1);
	operand = cd_operand(data.argv[0]);
	oldpwd = getcwd(NULL, 0);
	if (!operand)
	{
		builtin_setenv((char*[]){"setenv", "OLDPWD", oldpwd, NULL}, NULL);
		cd_setpwd();
	}
	else if ((ret = ft_cd(operand, data.flags)))
		builtin_setenv((char*[]){"setenv", "OLDPWD", oldpwd, NULL}, NULL);
	ft_strdel(&operand);
	ft_strdel(&oldpwd);
	return (ret);
}
