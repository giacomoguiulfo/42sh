/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:52:17 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/02 23:49:50 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	qsort_swap(void **v, int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void		ft_qsort(void **v, int left, int right,
										int (*comp)(const void *, const void *))
{
	int i;
	int last;

	if (left >= right)
		return ;
	qsort_swap(v, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if ((*comp)(v[i], v[left]) < 0)
			qsort_swap(v, ++last, i);
		++i;
	}
	qsort_swap(v, left, last);
	ft_qsort(v, left, last - 1, comp);
	ft_qsort(v, last + 1, right, comp);
}
