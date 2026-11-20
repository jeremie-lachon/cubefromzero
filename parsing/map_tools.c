#include "cub3d.h"

char	*remove_end(char *str)
{
	char	*tmp;

	tmp = cb_strchr(str, '\n');
	if (!tmp)
		return (cb_strdup(str));
	tmp = cb_substr(str, 0, tmp - str);
	return (tmp);
}

void	nswe(int i, int j, char *str, t_parse *parse)
{
	parse->map[i][j] = SPACE;
	parse->player[PLAYER_Y] = i + 0.5;
	parse->player[PLAYER_X] = j + 0.5;
	if (str[j] == 'N')
		parse->player[ANGLE] = 0.5;
	else if (str[j] == 'E')
		parse->player[ANGLE] = 1;
	else if (str[j] == 'S')
		parse->player[ANGLE] = 1.5;
	else
		parse->player[ANGLE] = 0;
	parse->player[PLAYER_COUNT] += 1.0;
}

int	fillmap(t_list *node, t_parse *parse, int i)
{
	int		j;
	char	*str;

	str = (char *)node->data;
	j = -1;
	while (++j < parse->width && str[j])
	{
		if (str[j] == '0')
			parse->map[i][j] = SPACE;
		else if (str[j] == '1')
			parse->map[i][j] = WALL;
		else if (str[j] == 'D')
			parse->map[i][j] = DOOR;
		else if (str[j] == 'P')
			parse->map[i][j] = SPRITE;
		else if (cb_strchr("NSEW", str[j]))
			nswe(i, j, str, parse);
		else if (str[j] == ' ')
			parse->map[i][j] = OUT;
		else
			return (printf("Error\nIncorrect map information\n"), 1);
	}
	while (j < parse->width)
		parse->map[i][j++] = OUT;
	return (0);
}

int	mapcheckandstock(t_list *list, t_parse *map)
{
	int		i;
	t_list	*tmp;

	map->height = listsize(list);
	map->map = cb_calloc(sizeof(int *), map->height);
	if (!map->map)
		return (perror("Error\n"), listfree(list), 1);
	map->width = maxsize(list);
	i = 0;
	tmp = list;
	while (i < map->height)
	{
		map->map[i] = cb_calloc(sizeof(int), map->width);
		if (!map->map[i])
			return (perror("Error\n"), listfree(list), intfree(&map->map, i), 1);
		if (fillmap(tmp, map, i))
			return (listfree(list), intfree(&map->map, i + 1), 1);
		tmp = tmp->next;
		i++;
	}
	return (listfree(list), checkmap(map));
}

int	mapper(int fd, t_parse *parse, char *str)
{
	t_list	*list;
	t_list	*new;

	list = 0;
	new = listnew(remove_end(str));
	if (!new)
		return (free(str), 1);
	listaddfront(&list, new);
	while (str)
	{
		free(str);
		str = custom_read(fd, 1);
		if (!str || *str == '\n')
			break ;
		new = listnew(remove_end(str));
		if (!new)
			return (free(str), listfree(list), 1);
		listaddfront(&list, new);
	}
	if (str)
		return (printf("Error\nWrong number of parameters\n"), \
		free(str), listfree(list), 1);
	if (mapcheckandstock(list, parse))
		return (free(str), 1);
	return (free(str), 0);
}
