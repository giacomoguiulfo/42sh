/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 21:57:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:59:48 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

void	msh_run_prog(char *executable, char **args, t_darr *newenvp)
{
	pid_t	pid;
	int		status;
	char	**env;

	env = msh_cp_env(newenvp);
	pid = fork();
	if (pid == 0)
	{
		if (execve(executable, args, env) == -1)
		{
			ft_dprintf(2, "msh: permission denied: %s\n", executable);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_dprintf(2, "msh: unable to fork process: %d\n", pid);
		exit(EXIT_FAILURE);
	}
	wait(&status);
	free(env);
}

int		msh_launch_bins(char **args, t_darr *newenvp)
{
	char	**bins;
	char	*executable;
	int		i;

	i = 0;
	bins = ft_strsplit(msh_get_env(newenvp, "PATH"), ':');
	while (bins[i])
	{
		executable = msh_check_bin(args[0], bins[i]);
		if (executable != NULL)
		{
			ft_free_sstr(bins);
			free(args[0]);
			args[0] = executable;
			msh_run_prog(executable, args, newenvp);
			return (1);
		}
		else
			i++;
	}
	ft_free_sstr(bins);
	return (0);
}

int		msh_launch_reg(char *prog, char **args, t_darr *newenvp)
{
	struct stat statbuf;

	if (lstat(prog, &statbuf) == -1)
		return (-1);
	msh_run_prog(prog, args, newenvp);
	return (0);
}

int		msh_run_builtins(char **args, t_darr *newenvp)
{
	if (!ft_strcmp(args[0], "cd"))
		return (msh_cd(args, newenvp));
	else if (!ft_strcmp(args[0], "echo"))
		return (msh_echo(args, newenvp));
	else if (!ft_strcmp(args[0], "exit") || !ft_strcmp(args[0], "EXIT"))
		return (msh_exit(args));
	else if (!ft_strcmp(args[0], "help"))
		return (msh_help(args));
	else if (!ft_strcmp(args[0], "env"))
		return (msh_displ_env(newenvp));
	else if (!ft_strcmp(args[0], "setenv"))
		return (msh_setenv(args, newenvp));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (msh_unsetenv(args, newenvp));
	return (-1);
}

int		msh_execute(char **args, t_darr *newenvp)
{
	int ret;

	if (args[0] == NULL)
		return (1);
	ret = msh_run_builtins(args, newenvp);
	if (ret != -1)
	{
		return (ret);
	}
	if (msh_launch_reg(args[0], args, newenvp) == -1)
	{
		if (msh_env_idx(newenvp, "PATH") == -1 ||
			!msh_launch_bins(args, newenvp))
			ft_dprintf(2, "msh: command not found: %s\n", args[0]);
	}
	return (1);
}
