#include "cub3d.h"

void	printmap(t_parse *parse)
{
	int	i;
	int	j;

	i = parse->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < parse->width)
		{
			printf("%d", parse->map[i][j]);
			j++;
		}
		printf("\n");
		i--;
	}
}

static void	gnlfree(int fd)
{
	char	*buf;

	buf = get_next_line(fd);
	while (buf)
	{
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
}

int	parse_filler(int fd, t_parse *cube)
{
	char	*buff;
	int		check;

	buff = custom_read(fd, 0);
	check = parse_filler2(buff, cube);
	while (!check)
	{
		buff = custom_read(fd, 1);
		check = parse_filler2(buff, cube);
	}
	if (check == 1)
		return (printf("Error\nMissing information\n"), gnlfree(fd), 1);
	if (mapper(fd, cube, buff))
		return (gnlfree(fd), 1);
	return (gnlfree(fd), 0);
}
