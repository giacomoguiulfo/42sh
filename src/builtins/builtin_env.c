/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:31:19 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/11 16:54:29 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ENV_ENOENT			"env: %s: No such file or directory"
#define ENV_EACCES			"env: %s: Permission denied"
#define ENV_OPT_LI			(1 << 0)
#define ENV_HAS_OPT_LI(a)	(a & ENV_OPT_LI)

static t_optsdata g_envopts =
{
	"env", NULL, NULL, NULL, 0, true, 0, {
		{'i', NULL, NULL, NULL, NULL, ENV_OPT_LI, 0, NULL, 0, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

static int	env_exec(char **av, char **env)
{
	pid_t	pid;
	int		status;

	if (IS_CHILD(pid = fork()))
	{
		if (access(*av, F_OK) != 0)
			exit(SH_ERR2_R1(ENV_EACCES, *av));
		if (ft_isdir(*av) || access(*av, X_OK) != 0)
			exit(SH_ERR2_R1(ENV_EACCES, *av));
		execve(*av, av, env);
	}
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status));
}

static void	get_exec_env(char ***av, char ***env)
{
	while (**av && ft_strchr(**av, '='))
	{
		*env = ft_sstrpush(*env, **av);
		(*av)++;
	}
}

int			builtin_env(char **av)
{
	t_optparser	data;
	char		**exec_env;

	data.flags = 0;
	if (ft_opts(av, &g_envopts, &data, true))
		return (1);
	exec_env = ENV_HAS_OPT_LI(data.flags) ? 0 : ft_sstrdup(sh_singleton()->env);
	get_exec_env(&data.argv, &exec_env);
	if (!*data.argv)
	{
		ft_sstrputs(exec_env);
		return (0);
	}
	return (env_exec(data.argv, exec_env));
}
