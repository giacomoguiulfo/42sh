/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:45:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/25 15:27:54 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_H
# define SYS_H

# include <unistd.h>

# define STDIN  STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO
# define IS_CHILD(pid) (pid == 0)

char	*ft_getenv(char **env, char *key);
int		ft_isdir(const char *path);
int		ft_unixcase(const char *str);

#endif
