/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:04:45 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:00:09 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "libft.h"

char	*ft_strrev(char *str)
{
	int start;
	int end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		ft_swap(str + start, str + end, sizeof(char));
		start++;
		end--;
	}
	return (str);
}
