/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

typedef struct	s_cmd_extractor
{
	bool		found_bin;
	char		*start;
	char		*end;
	char		*bin_start;
	char		*bin_end;
	char		buff[MAX_PATH_BIN_SIZE];
	int			x;
}				t_cmd_extractor;


void	tokenize_constructor(t_cmd_extractor *help, char *instr)
{
	help->found_bin = false;
	help->start = instructions;
	help->end = NULL;
	help->bin_start = NULL;
	help->bin->end = NULL;
	ft_bzero((void*)buff, MAX_PATH_BIN_SIZE);
	help->x = -1;
}

void	tokenize(char *instructions)
{
	t_cmd_extractor help;

	help.start = instructions;
	tokenize_constructor(&help, instructions);
}