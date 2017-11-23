/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:58:00 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:59:15 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void	msh_chenv_pwd(t_darr *newenvp, char *oldcwd)
{
	char buff[PATH_MAX + 1];
	char *newcwd;
	char *tmp;
	char **args;

	ft_asprintf(&tmp, "NULL OLDPWD %s", oldcwd);
	args = ft_strsplit(tmp, ' ');
	msh_setenv(args, newenvp);
	ft_free_sstr(args);
	free(tmp);
	newcwd = getcwd(buff, PATH_MAX + 1);
	ft_asprintf(&tmp, "NULL PWD %s", newcwd);
	args = ft_strsplit(tmp, ' ');
	msh_setenv(args, newenvp);
	ft_free_sstr(args);
	free(tmp);
}

int		msh_cd_multi(char **args, t_darr *newenvp, char *cwd)
{
	char	*ctemp[2];
	char	*res;
	int		i;
	int		idx;

	i = 0;
	while (args[i])
		i++;
	if (i == 3 && (res = ft_strstr(cwd, args[1])))
	{
		idx = res - cwd;
		i = ft_strlen(args[1]);
		ctemp[0] = ft_strndup(cwd, idx);
		ctemp[1] = ft_strdup(cwd + idx + i);
		ft_asprintf(&res, "%s%s%s", ctemp[0], args[2], ctemp[1]);
		if (chdir(res) != 0)
			ft_dprintf(2, "msh: unable to change directory\n");
		else
			msh_chenv_pwd(newenvp, res);
		free(res);
		free(ctemp[0]);
		free(ctemp[1]);
		return (0);
	}
	return (1);
}

void	msh_cd_ext(char **args, t_darr *newenvp, char *cwd)
{
	if (args[1][0] == '-' && args[1][1] == '\0')
	{
		if (chdir(msh_get_env(newenvp, "OLDPWD")) != 0)
			ft_dprintf(2, "msh: unable to change directory\n");
		else
		{
			msh_chenv_pwd(newenvp, cwd);
			ft_putendl(msh_get_env(newenvp, "PWD"));
		}
	}
	else if (args[1][0] == '$' && args[1][1] != '\0')
	{
		if (chdir(msh_get_env(newenvp, &args[1][1])) != 0)
			ft_dprintf(2, "msh: unable to change directory\n");
		else
			msh_chenv_pwd(newenvp, cwd);
	}
	else if (msh_cd_multi(args, newenvp, cwd) == 0)
		;
	else if (chdir(args[1]) != 0)
		ft_dprintf(2, "msh: unable to change directory\n");
	else
		msh_chenv_pwd(newenvp, cwd);
}

int		msh_cd(char **args, t_darr *newenvp)
{
	char *tmp;
	char buff[PATH_MAX + 1];
	char *cwd;

	cwd = getcwd(buff, PATH_MAX + 1);
	if (args[1] == NULL)
	{
		if (chdir(msh_get_env(newenvp, "HOME")) != 0)
			ft_dprintf(2, "msh: unable to change directory\n");
		else
			msh_chenv_pwd(newenvp, cwd);
	}
	else if (args[1][0] == '~')
	{
		ft_asprintf(&tmp, "%s/%s", msh_get_env(newenvp, "HOME"), &args[1][1]);
		if (chdir(tmp) != 0)
			ft_dprintf(2, "msh: unable to change directory\n");
		else
			msh_chenv_pwd(newenvp, cwd);
		free(tmp);
	}
	else
		msh_cd_ext(args, newenvp, cwd);
	return (1);
}
