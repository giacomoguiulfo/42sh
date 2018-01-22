/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:53:37 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/22 13:20:08 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

char		*msh_put_arrow(void)
{
	char	*cwd;
	char	buff[PATH_MAX];
	char	*prompt;

	cwd = ft_getenv(sh_singleton()->env, "PWD");
	if (!cwd)
		cwd = getcwd(buff, PATH_MAX);
	if (ft_strlen(cwd) == 1)
		return (ft_strdup("/ $> "));
	ft_asprintf(&prompt, "%s $> ", ft_basename(cwd));
	return (prompt);
}
