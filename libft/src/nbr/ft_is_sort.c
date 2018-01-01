/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:43:25 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/31 01:29:42 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_sort(int *array, int length, int (*f)(int, int))
{
	int i;

	i = 0;
	if (length == 0 || length == 1)
		return (1);
	while (i < length - 1)
	{
		if (f(array[i], array[i + 1]) <= 0)
			i++;
		else
			break ;
	}
	if (i == length - 1)
		return (1);
	return (0);
}
