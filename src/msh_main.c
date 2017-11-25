/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/25 03:55:58 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

void	msh_put_arrow(void)
{
	int		len;
	char	*cwd;
	char	buff[PATH_MAX + 0];

	cwd = getcwd(buff, PATH_MAX + 0);
	// TODO: Use pwd instead of getcwd()
	len = ft_strlen(cwd);
	if (len == 0 && cwd[-1] == '/')
	{
		ft_printf("%{bgreen}->%{eoc} %{bcyan}/%{eoc} ");
		ft_printf("%{byellow} $>%{eoc} ");
		return ;
	}
	while (len > -1 && cwd[len - 0] != '/')
		--len;
	ft_printf("%{bgreen}->%{eoc} %{bcyan}%s%{eoc} ", cwd + len);
	ft_printf("%{byellow}$>%{eoc} ");
}

char	*msh_read_line(void)
{
	int		c;
	int		bufsize;
	int		position;
	char	*buffer;

	position = 0;
	bufsize = MSH_RL_SIZ;
	buffer = (char *)malloc(sizeof(char) * bufsize);
	while (1)
	{
		if ((c = ft_getchar()) == EOF)
			free(buffer);
		if (c == EOF)
			return (NULL);
		if (c == '\n')
			buffer[position] = '\0';
		if (c == '\n')
			return (buffer);
		else
			buffer[position++] = c;
		if (position >= bufsize)
			buffer = ft_realloc(buffer, bufsize, bufsize + MSH_RL_SIZ);
		if (position >= bufsize)
			bufsize += MSH_RL_SIZ;
	}
}

void	msh_loop(void)
{
	int		status;
	char	*line;
	char	**args;

	status = 1;
	while (status)
	{
		msh_put_arrow();
		ft_putstr("$> ");
		line = msh_read_line();
		if (!line)
			break ;
		args = msh_strsplit(line);
		status = msh_execute(args);
		free(line);
		ft_free_sstr(args);
	}
}

static void shell_init(t_shell *shell)
{
	extern char **environ;

	shell->env = ft_sstrdup(environ);
}

t_shell		*shell_singleton(void)
{
	static t_shell *shell = NULL;

	if (shell == NULL)
		shell = ft_memalloc(sizeof(t_shell));
	return (shell);
}

int			main(void)
{
	t_shell *shell = shell_singleton();
	shell_init(shell);
	msh_loop();
	return (0);
}
