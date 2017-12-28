/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/16 20:22:50 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "builtins.h"
# include "libft.h"

# define SH_MSG(s, ...)     "%{bred}%s: " s "%{eoc}\n", g_argv[0], ##__VA_ARGS__
# define SH_ERR(s, ...)     ft_dprintf(STDERR, SH_MSG(s, ##__VA_ARGS__))
# define SH_ERR_R1(s, ...)  ((SH_ERR(s, ##__VA_ARGS__)) ? 1 : 1)

typedef struct			s_astree
{
	char				*type;
	int					ret;
	int					pipe_fd[2];
	struct s_asttoken	*this;
	struct s_astree		*left;
	struct s_astree		*right;
}						t_astree;

typedef struct			s_cmds
{
	bool				init;
	bool				hit_end;
	char				*cmd;
	struct s_cmds		*current;
	struct s_cmds		*end;
	struct s_cmds		*next;
	struct s_cmds		*prev;
}						t_cmds;

typedef struct  		s_shell
{
	bool				quit;
	char				*path;
	char				*term_name;
	char				**argv;
	char				**env;
	int					argc;
	int					stdout_backup;
	int					stdin_backup;
	int					stderr_backup;
	struct s_cmds		*history;
}						t_shell;

typedef struct			s_tokelist
{
	char				type[3];
	int					len;
	int					redir_prefix_fd;
	int					redir_suffix_fd;
	char				*redir_suffix_file;
	bool				redir_turn_off;
	struct s_tokelist	*next;
	struct s_tokelist	*last;
	void				*content;
}						t_tokelist;

int     	sh_init();
t_shell 	*sh_singleton();
void		sh_shutdown();
char		*readline(char *prompt);
t_tokelist	*lexer(char **cmds);
char		*msh_put_arrow(void);
char		**msh_strsplit(char *line);

t_astree	*parser(t_tokelist *abstract);

#endif
