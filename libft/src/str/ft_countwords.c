/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:50:14 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 20:41:46 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_countwords(char const *s, char c)
{
	int words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
			words++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (words);
}
