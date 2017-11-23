/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:24:50 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:53:23 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		msh_displ_env(t_darr *newenvp)
{
	int i;

	i = 0;
	while (i < newenvp->len)
	{
		if (newenvp->content[i] != NULL)
			ft_putendl(newenvp->content[i]);
		++i;
	}
	return (1);
}

int		msh_env_idx(t_darr *newenvp, char *var)
{
	int i;

	i = 0;
	while (i < newenvp->len)
	{
		if (newenvp->content[i] && msh_envcmp(newenvp->content[i], var))
			return (i);
		i++;
	}
	return (-1);
}

int		msh_unsetenv(char **args, t_darr *newenvp)
{
	char	*lookup;

	if (!args[1])
		return (1);
	lookup = msh_get_env(newenvp, args[1]);
	if (!lookup)
	{
		return (1);
	}
	free(ft_darr_remove(newenvp, msh_env_idx(newenvp, args[1])));
	return (1);
}

int		msh_concat_env(char **ret, char *str, t_darr *newenvp)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != ':' && str[i] != '\'')
		i++;
	tmp = ft_strndup(str + 1, (i > 0) ? i - 1 : i);
	if (msh_get_env(newenvp, tmp))
	{
		if (str[i] == ':')
			ft_asprintf(ret, "%s%s", msh_get_env(newenvp, tmp), &str[i]);
		else if (str[i] == '\'')
			ft_asprintf(ret, "%s%s", msh_get_env(newenvp, tmp), str + i + 1);
		else
			ft_asprintf(ret, "%s", msh_get_env(newenvp, tmp));
	}
	else
		*ret = ft_strdup("");
	free(tmp);
	return (1);
}

int		msh_setenv(char **args, t_darr *newenvp)
{
	char	*tmp;
	char	*grd;

	if (!args[1] || !args[2])
		return (1);
	if (ft_strchr(args[1], '=') || ft_strchr(args[2], '=') ||
		msh_env_inval(args[1]))
		return (1);
	if (args[2][0] == '$')
	{
		msh_concat_env(&tmp, args[2], newenvp);
		grd = tmp;
		ft_asprintf(&tmp, "%s=%s", args[1], tmp);
		free(grd);
	}
	else
		ft_asprintf(&tmp, "%s=%s", args[1], args[2]);
	if (msh_get_env(newenvp, args[1]) != NULL)
		return (msh_senv_helper(args[1], newenvp, tmp));
	ft_darr_push(newenvp, tmp);
	return (1);
}
