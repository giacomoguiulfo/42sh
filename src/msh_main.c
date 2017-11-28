/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 02:08:52 by giacomo          ###   ########.fr       */
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

void	msh_init_envp(t_darr *newenvp)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	while (environ[i])
		ft_darr_push(newenvp, ft_strdup(environ[i++]));
}

static void	sh_shutdown(t_terminal *config)
{
	struct termios revert;

	tcgetattr(0, &revert);
	revert.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &revert);
	ft_darr_kill(config->newenvp);
	return ;
}

static int	sh_init(t_terminal *config)
{
	struct termios change;

	if ((tgetent(NULL, getenv("TERM")) < 1))
		return (0);
	if ((config->name == getenv("xterm-256color")) == 0)
		ft_dprintf(2, "Opps, problem with terminal name\n");
	tcgetattr(0, &change);
	change.c_lflag &= ~(ICANON | ECHO);
	change.c_cc[VMIN] = 1;
	change.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &change);
	config->newenvp = ft_darr_init(sizeof(char *), 50);
	config->status = 1;
	return (1);
}

void	msh_loop(t_terminal *config)
{
	char	*line;
	char	**args;
	size_t	prompt;

	while (config->status)
	{
		prompt = msh_put_arrow();
		line = readline(prompt);
		ft_putchar('\n');
		if (!line)
			continue ;
		args = msh_strsplit(line);
		config->status = msh_execute(args);
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

	t_terminal config;
	if (!sh_init(&config))
		return (0);
	msh_loop(&config);
	sh_shutdown(&config);
	return (0);
}
