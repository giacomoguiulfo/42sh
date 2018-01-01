#include <stddef.h>

size_t ft_sstrlen(char *const sstr[])
{
	size_t i;

	i = 0;
	while (sstr[i])
		i++;
	return (i);
}
