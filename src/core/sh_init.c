/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 03:17:38 by giacomo           #+#    #+#             */
/*   Updated: 2018/01/12 13:50:55 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "history.h"
#include "libft.h"
#include <term.h>
#include <termios.h>

static char	*get_path(t_shell *shell)
{
	char	*path;
	int		x;

	path = NULL;
	x = -1;
	while (shell->env[++x])
	{
		if (ft_strncmp(shell->env[x], "PATH=", 5) == 0)
		{
			path = shell->env[x];
			break ;
		}
	}
	return (path);
}

void		sh_init_termios(void)
{
	struct termios term;

	tcgetattr(STDIN, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[0] = 0;
	tcsetattr(STDIN, TCSANOW, &term);
}

static void	init_shlvl(char **env)
{
	char	*shlvl;
	char	*newlvl;

	shlvl = ft_getenv(env, "SHLVL");
	newlvl = (shlvl) ? ft_itoa(ft_atoi(shlvl) + 1) : ft_strdup("1");
	builtin_setenv((char*[]){"setenv", "SHLVL", newlvl, NULL});
	ft_strdel(&newlvl);
}

int			sh_data_init(t_shell *shell, int ac, char **av, t_cmds *history)
{
	extern char **environ;
	int			ret;

	shell->quit = false;
	shell->argc = ac;
	shell->argv = ft_sstrdup(av);
	shell->env = ft_sstrdup(environ);
	shell->localenv = NULL;
	shell->path = get_path(shell);
	shell->stdin_backup = dup(0);
	shell->stdout_backup = dup(1);
	shell->stderr_backup = dup(2);
	history_constructor(shell, history);
	if (!(shell->term_name = ft_getenv(shell->env, "TERM")))
		shell->term_name = "dumb";
	if (ft_strequ(shell->term_name, "dumb"))
		return (SH_ERR_R1("Don't be dumb!"));
	if ((ret = tgetent(NULL, shell->term_name)) < 0)
		return (SH_ERR_R1("Trash: Unable to access termcap database\n"));
	else if (ret == 0)
		return (SH_ERR_R1("Trash: Terminal type is not defined\n"));
	init_shlvl(shell->env);
	sh_init_signals();
	return (0);
}

int			sh_init(int ac, char **av, t_cmds *history)
{
	t_shell *shell;

	shell = sh_singleton();
	sh_init_termios();
	if (sh_data_init(shell, ac, av, history))
		return (1);
	return (0);
}
