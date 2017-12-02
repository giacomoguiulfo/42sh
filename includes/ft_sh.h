/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "builtins.h"
# include "libft.h"

# define SH_MSG(s, ...)     "%{bred}%s: " s "%{eoc}\n", g_argv[0], ##__VA_ARGS__
# define SH_ERR(s, ...)     ft_dprintf(STDERR, SH_MSG(s, ##__VA_ARGS__))
# define SH_ERR_R1(s, ...)  ((SH_ERR(s, ##__VA_ARGS__)) ? 1 : 1)

typedef struct		s_cmds
{
	bool			init;
	bool			hit_end;
	char			*cmd;
	struct s_cmds	*current;
	struct s_cmds	*end;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

typedef struct  	s_shell
{
	char			**env;
	int           	argc;
	char          	**argv;
	struct s_cmds	*history;
}					t_shell;

int     sh_init();
t_shell *sh_singleton();
void	sh_shutdown();
int		msh_execute(char **args);
char	*readline(char *prompt);
void	lexer(char *cmds);
char	*msh_put_arrow(void);
char	**msh_strsplit(char *line);

#endif
