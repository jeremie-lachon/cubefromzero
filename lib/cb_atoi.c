#include "cub3d.h"

int	cb_atoi(const char *nptr)
{
	int			i;
	long		sign;
	long		res;

	sign = 1;
	i = 0;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] <= 13 && nptr[i] >= 9))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (nptr[i] < '0' || nptr[i] > '9')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + nptr[i++] - '0';
	return ((int)(res * sign));
}
