/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 03:17:38 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/24 13:21:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <term.h>
#include <termios.h>

void    history_constructor(t_shell *shell, t_cmds *history);

void	sh_init_termios(void)
{
	struct termios term;

	tcgetattr(STDIN, &term);
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
    term.c_cc[0] = 0;
	tcsetattr(STDIN, TCSANOW, &term);
}

static void init_shlvl(char **env)
{
	char	*shlvl;
	char	*newlvl;

	shlvl = ft_getenv(env, "SHLVL");
	newlvl = (shlvl) ? ft_itoa(ft_atoi(shlvl) + 1) : ft_strdup("1");
	builtin_setenv((char*[]){"setenv", "SHLVL", newlvl, NULL}, NULL);
	ft_strdel(&newlvl);
}

int sh_data_init(t_shell *shell, int ac, char **av, t_cmds *history)
{
    extern char **environ;
    int         ret;

    shell->quit = false;
    shell->argc = ac;
    shell->argv = ft_sstrdup(av);
    shell->env = ft_sstrdup(environ);
	shell->localenv = NULL;
    shell->stdin_backup = dup(0);
    shell->stdout_backup = dup(1);
    shell->stderr_backup = dup(2);
    history_constructor(shell, history);
    if (!(shell->term_name = ft_getenv(shell->env, "TERM")))
        shell->term_name = "dumb";
    if ((ret = tgetent(NULL, shell->term_name)) < 0)
        return (SH_ERR_R1("Unable to access termcap database"));
    else if (ret == 0)
        return (SH_ERR_R1("Terminal type is not defined"));
	init_shlvl(shell->env);
	return (0);
}

int sh_init(int ac, char **av, t_cmds *history)
{
    t_shell *shell;

    shell = sh_singleton();
    if (sh_data_init(shell, ac, av, history))
        return (1);
    sh_init_termios();
	return (0);
}
