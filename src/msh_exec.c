/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 21:57:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/23 17:13:10 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

t_strfmap	g_builtins[] =
{
	{"echo", &builtin_echo},
	{"cd", &builtin_cd},
	{"env", &builtin_env},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{NULL, NULL}
};

// void	msh_run_prog(char *executable, char **args)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	**env;
//
// 	env = msh_cp_env(newenvp);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(executable, args, env) == -1)
// 		{
// 			ft_dprintf(2, "msh: permission denied: %s\n", executable);
// 		}
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid < 0)
// 	{
// 		ft_dprintf(2, "msh: unable to fork process: %d\n", pid);
// 		exit(EXIT_FAILURE);
// 	}
// 	wait(&status);
// 	free(env);
// }
//
// int		msh_launch_bins(char **args)
// {
// 	char	**bins;
// 	char	*executable;
// 	int		i;
//
// 	i = 0;
// 	bins = ft_strsplit(msh_get_env(newenvp, "PATH"), ':');
// 	while (bins[i])
// 	{
// 		executable = msh_check_bin(args[0], bins[i]);
// 		if (executable != NULL)
// 		{
// 			ft_free_sstr(bins);
// 			free(args[0]);
// 			args[0] = executable;
// 			msh_run_prog(executable, args, newenvp);
// 			return (1);
// 		}
// 		else
// 			i++;
// 	}
// 	ft_free_sstr(bins);
// 	return (0);
// }
//
// int		msh_launch_reg(char *prog, char **args)
// {
// 	struct stat statbuf;
//
// 	if (lstat(prog, &statbuf) == -1)
// 		return (-1);
// 	msh_run_prog(prog, args);
// 	return (0);
// }

int		msh_run_builtins(char **args)
{
	int i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(g_builtins[i].name, args[0]) == 0)
			return (g_builtins[i].f(args, shell_singleton()->env));
		i++;
	}
	return (-1);
}

int		msh_execute(char **args)
{
	int ret;

	if (args[0] == NULL)
		return (1);
	ret = msh_run_builtins(args);
	ft_printf("ret: %d", ret);
	// if (ret != -1)
	// {
	// 	return (ret);
	// }
	// if (msh_launch_reg(args[0], args, newenvp) == -1)
	// {
	// 	if (msh_env_idx(newenvp, "PATH") == -1 ||
	// 		!msh_launch_bins(args, newenvp))
	// 		ft_dprintf(2, "msh: command not found: %s\n", args[0]);
	// }
	return (1);
}
