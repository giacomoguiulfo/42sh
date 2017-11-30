/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:53:37 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 02:20:39 by giacomo          ###   ########.fr       */
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
	size_t	len;
	char	*cwd;
	char	buff[PATH_MAX + 0];
	char	*prompt;

	cwd = getcwd(buff, PATH_MAX + 0);
	len = ft_strlen(cwd);
	if (len == 0 && cwd[-1] == '/')
	{
		prompt = ft_strdup("-> /  $> ");
		ft_putstr(prompt);
		return (prompt);
	}
	while (len > 0 && cwd[len - 0] != '/')
		--len;
	ft_asprintf(&prompt, "%s/%s/%s", cwd + len, "-> ", " $> ");
	ft_putstr(prompt);
	return (prompt);
}
//
// int		msh_envcmp(char *env, char *lookup)
// {
// 	char	*ret;
// 	int		i;
//
// 	i = 0;
// 	while (env[i] != '=' && env[i] != '\0')
// 		i++;
// 	if (env[i] == '\0')
// 		return (0);
// 	ret = ft_strndup(env, i);
// 	if (!ft_strcmp(ret, lookup))
// 	{
// 		free(ret);
// 		return (1);
// 	}
// 	free(ret);
// 	return (0);
// }
//
// char	*msh_get_env(t_darr *newenvp, char *look)
// {
// 	int i;
//
// 	i = -1;
// 	while (++i < newenvp->len)
// 	{
// 		if (newenvp->content[i] == NULL)
// 			continue ;
// 		if (msh_envcmp(newenvp->content[i], look))
// 			return (ft_strchr(newenvp->content[i], '=') + 1);
// 	}
// 	return (NULL);
// }
//
// char	**msh_cp_env(t_darr *newenvp)
// {
// 	char	**ret;
// 	int		i;
// 	int		size;
//
// 	i = -1;
// 	size = 0;
// 	while (++i < newenvp->len)
// 		if (newenvp->content[i] != NULL)
// 			size++;
// 	ret = (char **)ft_memalloc(sizeof(char *) * (size + 1));
// 	i = -1;
// 	size = 0;
// 	while (++i < newenvp->len)
// 	{
// 		if (newenvp->content[i] != NULL)
// 			ret[size++] = newenvp->content[i];
// 	}
// 	return (ret);
// }
//
// char	*msh_check_bin(char *executable, char *path)
// {
// 	struct stat	statbuf;
// 	char		*ret;
//
// 	ft_asprintf(&ret, "%s/%s", path, executable);
// 	if (lstat(ret, &statbuf) == -1)
// 	{
// 		free(ret);
// 		return (NULL);
// 	}
// 	else if ((statbuf.st_mode & S_IFMT) == S_IFREG)
// 		return (ret);
// 	return (NULL);
// }