#include "cub3d.h"

char	*custom_read(int fd, int check)
{
	char	*buf;

	while (1)
	{
		buf = get_next_line(fd);
		if (!buf || check)
			return (buf);
		if (*buf != '\n')
			return (buf);
		free(buf);
	}
}

char	*cb_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	c = c % 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			ptr = (char *)s + i;
			return ((char *)ptr);
		}
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	ptr = 0;
	return (ptr);
}

char	*cb_substr(char const *s, int start, int len)
{
	int		i;
	int		j;
	char	*copy;

	if (start < 0)
		return (0);
	if (start > (int)cb_strlen(s))
		return (cb_calloc(1, 1));
	if (len + start <= (int)cb_strlen(s))
		copy = (char *)malloc(sizeof(char) * (len + 1));
	else
		copy = (char *)malloc(sizeof(char) * (cb_strlen(s + start) + 1));
	if (!copy)
		return (NULL);
	i = -1;
	j = -1;
	while (s[++i])
	{
		if (i >= start && ++j < len)
			copy[j] = s[i];
	}
	copy[j] = 0;
	return (copy);
}

int	sett(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (!cb_strchr(" \t\v\f\r", str[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	skip(char *s, int *i, int check)
{
	int	com;

	com = 0;
	while (cb_strchr(" \t\v\f\r", s[*i]))
		(*i)++;
	if (check)
		while (s[*i] <= '9' && s[*i] >= '0')
			(*i)++;
	while (cb_strchr(" \t\v\f\r,", s[*i]))
	{
		if (s[*i] == ',')
			com++;
		(*i)++;
	}
	return (com);
}
