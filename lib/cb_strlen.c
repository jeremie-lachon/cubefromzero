#include "cub3d.h"

size_t	cb_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*str++)
		a++;
	return (a);
}
