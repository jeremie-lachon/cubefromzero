#include "get_next_line.h"

char	*cb_extract(int fd, char *buff, ssize_t check, char **str)
{
	char	*new;

	new = malloc(sizeof(char) * 1);
	if (!new)
		return (cb_freegnl(str, 0));
	*new = 0;
	check = BUFFER_SIZE;
	while (check == BUFFER_SIZE)
	{
		check = read(fd, buff, BUFFER_SIZE);
		if (!check && !*new)
			return (cb_freegnl(&new, 0));
		buff[check] = 0;
		cb_stlenchec(buff, &check, 0);
		new = cb_stcpy(buff, new, 0, 0);
		if (!new)
			return (cb_freegnl(str, new));
	}
	if (check < 0)
		return (cb_freegnl(str, new));
	return (new);
}

int	cb_checkbuffer(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*cb_gnlstocker(char **str)
{
	int		i;
	char	*st;
	char	*ret;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	if ((*str)[i] == '\n')
		i++;
	ret = cb_stcpy(*str, 0, i, 1);
	if (!ret)
		return (cb_freegnl(str, 0));
	if (!((*str)[i]))
		st = 0;
	else
	{
		st = cb_stcpy(*str + i, 0, cb_stlenchec(*str + i, 0, 1), 1);
		if (!st)
			return (cb_freegnl(str, ret));
	}
	free(*str);
	*str = st;
	return (ret);
}

int	cb_checker(char **str, int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (read(fd, 0, 0) != 0)
	{
		free(str[fd]);
		str[fd] = 0;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*fds[1024];
	char		*final;
	char		*buff;

	if (!cb_checker(fds, fd))
		return (cb_freegnl(&(fds[fd]), 0));
	if (cb_checkbuffer(fds[fd]))
		return (cb_gnlstocker(&(fds[fd])));
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (cb_freegnl(&(fds[fd]), 0));
	final = cb_extract(fd, buff, BUFFER_SIZE, &(fds[fd]));
	free(buff);
	if (!final)
	{
		if (fds[fd])
			return (cb_gnlstocker(&(fds[fd])));
		else
			return (0);
	}
	fds[fd] = cb_stcat(fds[fd], final);
	if (!(fds[fd]))
		return (cb_freegnl(&(fds[fd]), 0));
	return (cb_gnlstocker(&(fds[fd])));
}
