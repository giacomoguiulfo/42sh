#include "str.h"

void	ft_sstrdelone(char **sstr, int index)
{
	int i;

	ft_strdel(&sstr[index]);
	i = index;
	while (sstr[i] || i == index)
	{
		sstr[i] = sstr[i + 1];
		i++;
	}
}
