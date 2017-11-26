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

void	msh_init_envp(t_darr *newenvp)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	while (environ[i])
		ft_darr_push(newenvp, ft_strdup(environ[i++]));
}

void	sh_init(t_terminal *config)
{
	raw_terminal(config);
	config->newenvp = ft_darr_init(sizeof(char *), 50);
	config->status = 1;
}

void	msh_loop(void)
{
	char	*line;
	char	**args;
	t_terminal config;

	sh_init(&config);
	ft_printf("Terminal h: %zu, w: %zu\n", config.height, config.width);
	while (config.status)
	{
		config.prompt_size = msh_put_arrow();
		line = readline(&config);
		if (!line)
			break ;
		args = msh_strsplit(line);
		config.status = msh_execute(args, config.newenvp);
		free(line);
		ft_free_sstr(args);
	}
	ft_darr_kill(config.newenvp);
}

int		main(void)
{
	msh_loop();
	return (0);
}
