#include "get_next_line.h"

char	*cb_stcpy(char *str, char *a, int n, int check)
{
	char	*new;
	int		i;

	if (check)
	{
		i = -1;
		new = malloc(sizeof(char) * (n + 1));
		if (!new)
			return (0);
		while (++i < n)
			new[i] = str[i];
		new[i] = 0;
		return (new);
	}
	i = cb_stlenchec(str, 0, 1);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (cb_freegnl(&a, 0));
	new[i] = 0;
	while (i-- > 0)
		new[i] = str[i];
	return (cb_stcat(a, new));
}

char	*cb_stcat(char *a, char *b)
{
	int		i;
	int		j;
	char	*new;

	if (!a)
	{
		a = malloc(sizeof(char) * 1);
		if (!a)
			return (cb_freegnl(&b, 0));
		a[0] = 0;
	}
	new = malloc(sizeof(char) * (cb_stlenchec(a, 0, 1) + cb_stlenchec(b, 0, 1)
				+ 1));
	if (!new)
		return (cb_freegnl(&a, b));
	i = -1;
	j = 0;
	while (a[++i])
		new[i] = a[i];
	while (b[j])
		new[i++] = b[j++];
	new[i] = 0;
	cb_freegnl(&a, b);
	return (new);
}

int	cb_stlenchec(char *a, ssize_t *check, int ck)
{
	int	i;

	if (ck)
	{
		i = 0;
		while (a[i])
			i++;
		return (i);
	}
	while (*a)
	{
		if (*a == '\n')
			*check = 0;
		a++;
	}
	return (0);
}

char	*cb_freegnl(char **a, char *b)
{
	free(*a);
	*a = 0;
	if (b)
	{
		free(b);
		b = 0;
	}
	return (0);
}
