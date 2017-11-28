/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 03:49:17 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:59:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	msh_init_envp(t_darr *newenvp)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	while (environ[i])
		ft_darr_push(newenvp, ft_strdup(environ[i++]));
}

void	default_terminal(void)
{
	struct termios revert;

	tcgetattr(0, &revert);
	revert.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &revert);
	return ;
}

int		raw_terminal(t_terminal *config)
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
	return (1);
}

void	sh_init(t_terminal *config)
{
	raw_terminal(config);
	config->newenvp = ft_darr_init(sizeof(char *), 50);
	config->status = 1;
}

void	msh_loop(t_terminal *config)
{
	char	*line;
	char	**args;

	while (config->status)
	{
		config->prompt_size = msh_put_arrow();
		line = readline(config);
		if (!line)
			continue ;
		args = msh_strsplit(line);
		config->status = msh_execute(args, config->newenvp);
		free(line);
		ft_free_sstr(args);
	}
	ft_darr_kill(config->newenvp);
}

int		main(void)
{
	t_terminal config;

	raw_terminal(&config);
	msh_loop(&config);
	default_terminal();
	return (0);
}
