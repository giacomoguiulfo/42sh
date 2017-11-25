/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 21:08:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/13 01:12:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	msh_count_quotes(char **line, int *words, char quote, int *ret)
{
	*ret = 0;
	(*line)++;
	while ((**line) != quote && (**line))
		(*line)++;
	if (**line)
	{
		(*line)++;
		(*words)++;
	}
	else
		*ret = 1;
}

static int	msh_count_words(char *line)
{
	int	words;
	int ret;

	words = 0;
	while (*line)
	{
		while (*line <= 32 && *line != '\0')
			line++;
		if ((*line == '\"' && *(line + 1) != '\"') ||
			(*line == '\'' && *(line + 1) != '\''))
		{
			msh_count_quotes(&line, &words, *line, &ret);
			if (ret == 1)
				return (words);
		}
		if (*line > 32 && *line != '\"' && *line != '\'')
			words++;
		while (*line > 32 && *line != '\"' && *line != '\'')
			line++;
		if ((*line == '\"' && *(line + 1) == '\"') ||
			(*line == '\'' && *(line + 1) == '\''))
			line += 2;
	}
	return (words);
}

static char	*msh_handle_quotes(char *line, int *j, char quote)
{
	int size;

	size = 0;
	(*j)++;
	while (line[*j] != quote && line[*j])
	{
		size++;
		(*j)++;
	}
	if (line[*j])
	{
		(*j)++;
		return (ft_strndup(line + *j - size - 1, size));
	}
	else
		return (ft_strdup(""));
}

static char	*msh_next_word(char *line, int *j)
{
	int		size;

	while (line[*j])
	{
		while (line[*j] <= 32 && line[*j] != '\0')
			(*j)++;
		if ((line[*j] == '\"' && line[*j + 1] != '\"') ||
			(line[*j] == '\'' && line[*j + 1] != '\''))
			return (msh_handle_quotes(line, j, line[*j]));
		if (line[*j] > 32 && line[*j] != '\"' && line[*j] != '\'')
		{
			size = 0;
			while (line[*j + size] > 32 && line[*j + size] != '\"'
												&& line[*j + size] != '\'')
				size++;
			while (line[*j] > 32 && line[*j] != '\"' && line[*j] != '\'')
				(*j)++;
			return (ft_strndup(line + *j - size, size));
		}
		if ((line[*j] == '\"' && line[*j + 1] == '\"') ||
			(line[*j] == '\'' && line[*j + 1] == '\''))
			*j += 2;
	}
	return (NULL);
}

char		**msh_strsplit(char *line)
{
	int		i;
	int		j;
	int		words;
	char	**ret;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	words = msh_count_words(line);
	ret = (char **)ft_memalloc(sizeof(char *) * (words + 1));
	while (i < words)
		ret[i++] = msh_next_word(line, &j);
	return (ret);
}
