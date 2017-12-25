/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:31:19 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/25 00:23:47 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"

#define ENV_OPT_LI			(1 << 0)
#define ENV_HAS_OPT_LI(a)	(a & ENV_OPT_LI)

static t_optsdata g_envopts =
{
	"env", NULL, NULL, NULL, 0, true, 0, {
		{'i', NULL, NULL, NULL, NULL, ENV_OPT_LI, 0, NULL, 0, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

static void get_exec_env(char ***av, char **env)
{

}

int	builtin_env(char **av)
{
	t_optparser	data;
	char		**exec_env;

	data.flags = 0;
	if (ft_opts(av, &g_envopts, &data, true))
		return (1);
	exec_env = ENV_HAS_OPT_LI(data.flags) ? 0 : ft_sstrdup(sh_singleton()->env);
	get_exec_env(&data.argv, exec_env);
	if (!*data.argv)
	{
		ft_sstrputs(exec_env);
		return (0);
	}
	return (env_exec());
}
