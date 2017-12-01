/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 03:17:38 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/28 05:58:16 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <term.h>
#include <termios.h>

// TODO: Do we need this function?
// void	sh_shutdown()
// {
// 	struct termios term;
//
// 	tcgetattr(0, &term);
// 	term.c_lflag |= (ICANON | ECHO);
// 	tcsetattr(0, TCSADRAIN, &term);
// }

void	sh_init_termios(void)
{
	struct termios term;

	tcgetattr(STDIN, &term);
	term.c_lflag &= ~(ICANON | ECHO /*|ISIG*/ );
    //term.c_oflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
    term.c_cc[0] = 0;
	tcsetattr(STDIN, TCSANOW, &term);
}

int sh_data_init(int ac, char **av)
{
    t_shell     *shell;
    extern char **environ;
    char        *term_name;
    int         ret;

    shell = sh_singleton();
    shell->argc = ac;
    shell->argv = ft_sstrdup(av);
    shell->env = ft_sstrdup(environ);
    // TODO: INIT SHLVL
    // TODO: SH DEFAULT OPTS
    if (!(term_name = ft_getenv(shell->env, "TERM")))
        term_name = "dumb";
    if ((ret = tgetent(NULL, term_name)) < 0)
        return (SH_ERR_R1("Unable to access termcap database"));
    else if (ret == 0)
        return (SH_ERR_R1("Terminal type is not defined"));
	return (0);
}

int sh_init(int ac, char **av)
{
    if (sh_data_init(ac, av))
        return (1);
    sh_init_termios(); // TODO: Move this to a better place
	return (0);
}
