/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:56:48 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/08 17:53:50 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "gnl/get_next_line.h"
// settings check 0
// map      check 1

enum
{
	PLAYER_X,
	PLAYER_Y,
	ANGLE,
	PLAYER_COUNT
};

enum
{
	SPACE,
	WALL,
	OUT,
	DOOR,
	SPRITE
}

enum
{
	NO,
	WE,
	SO,
	EA,
	DO,
	SP
}

typedef struct s_list
{
	struct s_list *next;
	void *data;
}	t_list;

typedef struct s_parse
{
	char	**textures;
	int		F;
	int		C;
	float	player[4];
	int		**map;
	int		width;
	int		height;
}	t_parse;

typedef struct s_img_data
{
    void    *img_ptr;
    char    *adress;
    int     bpp;
    int     size;
    int     endl;
    int     pix_w;
    int     pix_h;
}   t_img_data;

typedef struct s_cube
{
	int **map;
	int	width;
	int	height;
	float	player[3];
	t_img_data	texture[5];
	int	nsprite;
	t_img_data	*sprite;
	
}	t_cube;


int	listfree(t_list *list)
{
	if (list)
	{
		listfree(list->next);
		free(list->data);
	}
	free(list);
	return (0);
}

int	listaddfront(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
	return (0);
}

t_list	*listnew(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->data = data;
	new->next = 0;
	return (new);
}

int	intfree(int **array, int i)
{
	int	j;

	if (!array)
		return (1);
	j = 0;
	while (j < i)
		free(array[j++]);
	free(array);
	return (0);
}

int	listsize(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	maxsize(t_list *list)
{
	int	maxlen;
	int	len;

	maxlen = -1;
	while (list)
	{
		len = strlen((char *)list->data);
		if (len > maxlen)
			maxlen = len;
		list = list->next;
	}
	return (maxlen);
}

static void gnlfree(int fd)
{
    char *buf;

    buf = get_next_line(fd);
    while (buf)
    {
        free(buf);
        buf = get_next_line(fd);
    }
    close(fd);
}

int	parsefree(t_parse *parse)
{
	int	i;

	i = 0;
	if (!parse)
		return (0);
	if (parse->map)
	{
		while (i < parse->height)
			free(parse->map[i++]);
		free(parse->map);
	}
	i = 0;
	while (i < 6)
		free(parse->textures[i++]);
	free(parse->textures)
	free(parse);
	return (0);
}

char *custom_read(int fd, int check)
{
    char *buf;

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

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	c = c % 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			ptr = (char *) s + i;
			return ((char *) ptr);
		}
		i++;
	}
	if (s[i] == c)
		return ((char *) s + i);
	ptr = 0;
	return (ptr);
}

char	*ft_substr(char const *s, int start, int len)
{
	int	i;
	int	j;
	char	*copy;
    if(start < 0)
        return (0);
	if (start > strlen(s))
		return (calloc(1, 1));
	if (len + start <= strlen(s))
		copy = (char *)malloc(sizeof(char) * (len + 1));
	else
		copy = (char *)malloc(sizeof(char) * (strlen(s + start) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			copy[j] = s[i];
			j++;
		}
		i++;
	}
	copy[j] = 0;
	return (copy);
}

int settings_split(char *str)
{
    int i;
    i = 2;

    while (str[i])
    {
        if (!ft_strchr(" \t\v\f\r", str[i]))
            return (i);
        i++;
    }
    return (-1);
}

int skip(char *s, int *i, int check)
{
	int com;

	com = 0;

	while (ft_strchr(" \t\v\f\r", s[*i]))
		(*i)++;
	if (check)
		while (s[*i] <= '9' && s[*i] >= '0')
			(*i)++;
	while (ft_strchr(" \t\v\f\r,", s[*i]))
	{
		if(s[*i] == ',')
			com++;
		(*i)++;
	}
	return (com);
}

int function(char *s)
{
    int i;
    int ret;
    int tmp;
    ret = 0;
    i = 1;
    if (skip(s, &i, 0) || !s[i])
        return (-1);
	tmp = atoi(s + i);
    if (tmp < 0 || tmp > 255)
        return (-1);
    ret = tmp << 16;
    if(skip(s, &i, 1) != 1 || !s[i])
        return (-1);
    tmp = atoi(s + i);
    if (tmp < 0 || tmp > 	255)
        return (-1);
    ret |= tmp << 8;
    if(skip(s, &i, 1) != 1 || !s[i])
        return (-1);
    tmp = atoi(s + i);
    if (tmp < 0 || tmp > 255)
        return (-1);
    ret |= tmp;
    return (ret);
}
// Trim

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t				i;
	unsigned char		*new;

	i = nmemb * size;
	if (i == 0)
	{
		new = malloc(0);
		if (!new)
			return (0);
		*new = 0;
		return (new);
	}
	if (i < nmemb || i < size)
		return (0);
	new = malloc(i);
	if (!new)
		return (0);
	while (i--)
		new[i] = 0;
	return (new);
}

static int	check_char(const char *set, char c)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static char	*strmalloc(int *tab)
{
	char	*new;

	if (tab[1] == 0)
		new = (char *)malloc(sizeof(char) * (tab[0]));
	else
		new = (char *)malloc(sizeof(char) * (tab[1] - tab[0] + 2));
	if (!new)
		return (0);
	return (new);
}

/*
	int		0	cur;
	int		1	end;
	int		2	new_count;
	*/
char	*ft_strtrim(char *s1, char const *set)
{
	char		*new;
	int			tab[3];

	tab[2] = 0;
	tab[0] = 0;
	if (!s1 || !set)
		return (0);
	while (check_char(set, s1[tab[0]]) && s1[tab[0]])
		tab[0]++;
	tab[1] = ft_strlen(s1) - 1;
	if (s1[0] == '\0' || tab[1] + 1 == tab[0])
		return (ft_calloc(sizeof(char), 1));
	while (check_char(set, s1[tab[1]]) && tab[1] > 0)
		tab[1]--;
	new = strmalloc(tab);
	if (!new)
		return (NULL);
	while (tab[0] <= tab[1])
		new[tab[2]++] = s1[tab[0]++];
	new[tab[2]] = 0;
	return (free(s1), new);
}
// ^ Trim
int cube_filler2(char *buf, t_parse *cube)
{
    char	*tmp;

    if (!buf)
        return (1);
	tmp = ft_strchr(buf, '\n');
	if (!tmp)
		return (1);
    if (!strncmp("NO ", buf, 3) && !cube->textures[NO])
        cube->NO = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
    else if (!strncmp("WE ", buf, 3) && !cube->textures[WE])
        cube->WE = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
    else if (!strncmp("SO ", buf, 3) && !cube->textures[SO])
        cube->SO = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
    else if (!strncmp("EA ", buf, 3) && !cube->textures[EA])
        cube->EA = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
    else if (!strncmp("F ", buf, 2) && !cube->F)
        cube->F = function(buf);
    else if (!strncmp("C ", buf, 2) && !cube->C)
        cube->C = function(buf);
    else if (!strncmp("DO ", buf, 3) && !cube->textures[DO])
        cube->WE = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
    else if (!strncmp("SP ", buf, 3) && !cube->textures[SP])
        cube->WE = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
    else
        return (2);
    return (free(buf), 0);
}

int	fillmap(t_list *node, t_parse *parse, int i)
{
	int	j;
	char	*str;

	str = (char *)node->data;
	j = 0;
	while (j < parse->width && str[j])
	{
		if (str[j] == '0')
			parse->map[i][j] = SPACE;
		else if (str[j] == '1')
			parse->map[i][j] = WALL;
		else if (str[j] == 'D')
			parse->map[i][j] = DOOR;
		else if (str[j] == 'P')
			parse->map[i][j] = SPRITE;
		else if (strchr("NSEW", str[j]))
		{
			parse->map[i][j] = SPACE;
			parse->player[PLAYER_X] = j + 0.5;
			parse->player[PLAYER_Y] = j + 0.5;
			if (str[j] == 'N')
				parse->player[ANGLE] = 0.5;
			else if (str[j] == 'E')
				parse->player[ANGLE] = 0;
			else if (str[j] == 'S')
				parse->player[ANGLE] = 1.5;
			else
				parse->player[ANGLE] = 1;
			parse->player[PLAYER_COUNT] += 1.0;
		}
		else if (str[j] == ' ')
			parse->map[i][j] = -1;
		else
			return (1);
		j++;
	}
	while (j < parse->width)
		parse->map[i][j++] = -1;
	return (0);
}

int	checksides(t_parse *parse, int i, int j)
{
	if (!i || i + 1 == parse->height)
		return (1);
	if (!j || j + 1 == parse->width)
		return (1);
	if (parse->map[i -1][j] == OUT)
		return (1);
	if (parse->map[i][j - 1] == OUT)
		return (1);
	if (parse->map[i][j + 1] == OUT)
		return (1);
	if (parse->map[i + 1][j] == OUT)
		return (1);
	return (0);
}

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

int	check_final_elements(t_parse *parse)
{
	if (!parse->textures[NO] || !parse->textures[EA] || !parse->textures[WE])
		return (1);
	if (!parse->textures[SO] || parse->C == -1 || parse->F == -1)
		return (1);
	return (0);
}

int	check_elements(t_parse *parse)
{
	int	spritedoor[2];
	int	i;
	int	j;

	if (parse->player[PLAYER_COUNT] != 1.0)
		return (1);
	spritedoor[0] = 0;
	spritedoor[1] = 0;
	i = 0;
	while (i < parse->height)
	{
		j = 0;
		while (j < parse->width)
		{
			if (parse->map[i][j] == SPRITE)
				spritedoor[0] = 1;
			else if (parse->map[i][j] == DOOR)
				spritedoor[1] = 1;
			j++;
		}
		i++;
	}
	if (!parse->textures[SP] && spritedoor[0])
		return (1);
	if (!parse->textures[DO] && spritedoor[1])
		return (1);
	return (check_final_elements(parse));
}

int	checkmap(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	printmap(parse);
	while (i < parse->height)
	{
		j = 0;
		while (j < parse->width)
		{
			if (parse->map[i][j] == 0)
				if (checksides(parse, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (check_elements(parse));
}

int	mapcheckandstock(t_list *list, t_parse *map)
{
	int	i;
	t_list	*tmp;

	map->height = listsize(list);
	map->map = calloc(sizeof(int *), map->height);
	if (!map->map)
		return (listfree(list), 1);
	map->width = maxsize(list);
	i = 0;
	tmp = list;
	while (i < map->height)
	{
		map->map[i] = calloc(sizeof(int), map->width);
		if (!map->map[i])
			return (listfree(list), intfree(map->map, i), 1);
		if (fillmap(tmp, map, i))
			return (listfree(list), intfree(map->map, i), 1);
		tmp = tmp->next;
		i++;
	}
	return (listfree(list), checkmap(map));
}

char	*remove_end(char *str)
{
	char	*tmp;

	tmp = strchr(str, '\n');
	if (!tmp)
		return (strdup(str));
	tmp = ft_substr(str, 0, tmp - str);
	return (tmp);
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
		return (free(str), listfree(list), 1);
	if (mapcheckandstock(list, parse))
		return (free(str), 1);
	return (free(str), 0);
}

int cube_filler(int fd, t_parse *cube)
{
    char *buff;
    int check;

	buff = custom_read(fd, 0);
	check = cube_filler2(buff, cube);
	while (!check)
	{
		buff = custom_read(fd, 1);
		check = cube_filler2(buff, cube);
	}
	if (check == 1)
		return (gnlfree(fd), 1);
	if (mapper(fd, cube, buff))
		return (gnlfree(fd), 1);
    return (gnlfree(fd) ,0);
}

int	cub_check(char *str)
{
	int	i;

	i = strlen(str);
	if (i < 5)
		return (1);
	i--;
	if (str[i] != 'b')
		return (1);
	if (str[i - 1] != 'u')
		return (1);
	if (str[i - 2] != 'c')
		return (1);
	if (str[i - 3] != '.')
		return (1);
	return (0);
}

t_parse	*cubeinit(void)
{
	t_parse	*parse;

	parse = calloc(sizeof(t_parse), 1);
	if (!parse)
		return (0);
	parse->textures = calloc(sizeof(char *), 6);
	if (!parse->textures)
		return (free(parse), 0);
	parse->C = -1;
	parse->F = -1;
	return (parse);
}

void	freetexts(t_parse *parse, t_cube *cube, int i)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		free(parse->textures[j]);
		parse->textures[j++] = 0;
	}
	j = 0;
	while (j < i)
		mlx_destroy_image(0, &cube->texture[j++]);
}

int	fillsides(t_cube *cube, t_parse *parse, t_mlx *mlx)
{
	cube->texture[NO].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, parse->textures[NO], &cube->texture[NO].pix_w, &cube->texture[NO].pix_h);
	if (!cube->texture[NO])
		return (freetexts(parse, cube, 0), 1);
	cube->texture[WE].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, parse->textures[WE], &cube->texture[WE].pix_w, &cube->texture[WE].pix_h);
	if (!cube->texture[WE])
		return (freetexts(parse, cube, 1), 1);
	cube->texture[SO].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, parse->textures[SO], &cube->texture[SO].pix_w, &cube->texture[SO].pix_h);
	if (!cube->texture[SO])
		return (freetexts(parse, cube, 2), 1);
	cube->texture[EA].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, parse->textures[EA], &cube->texture[EA].pix_w, &cube->texture[EA].pix_h);
	if (!cube->textures[EA])
		return (freetexts(parse, cube, 3), 1);
	if (parse->textures[DO])
		cube->texture[DO].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, parse->textures[DO], &cube->texture[DO].pix_w, &cube->texture[DO].pix_h);
	if (parse->textures[DO] && !cube->texture[DO])
		return (freetexts(parse, cube, 4), 1);
	return (freetexts(parse, cube, 0), 0);
}

t_cube	*parse_to_cube(t_parse *parse)
{
	t_cube	*cube;

	cube = calloc(sizeof(t_cube), 1);
	if (!cube)
		return (write(2, "Error\n", 6), parsefree(parse), 0);
	cube->map = parse->map;
	cube->height = parse->height;
	cube->width = parse->width;
	cube->player[PLAYER_X] = parse->player[PLAYER_X];
	cube->player[PLAYER_Y] = parse->player[PLAYER_Y];
	cube->player[ANGLE] = parse->player[ANGLE];
	if (fillsides(cube, parse))
		return (free(cube), parsefree(parse), 0);
	// fill sprite image
	return (cube);
}

int main(int ac, char **av)
{
    t_parse *parse;
    t_cube	*cube;
	int fd;

    if(ac != 2)
        return (perror("Wrong number of arguments.\n"), 1);
    if(cub_check(av[1]))
        return (perror("Map is not using .cub extension.\n"), 1);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (perror("Open"), 1);
    parse = cubeinit();
    if(!parse || cube_filler(fd, parse))
        return (write(2, "Error\n", 6), parsefree(parse), 1);
	printf("NO:%s:, SO:%s:, EA:%s:, WE:%s:\n", parse->textures[NO], parse->textures[SO], parse->textures[EA], parse->textures[WE]);
	printf("F %d:%d:%d C %d:%d:%d \n", (parse->F >> 16) & 0xFF, (parse->F >> 8) & 0xFF, parse->F & 0xFF, parse->C >> 16 & 255, parse->C >> 8 & 255, parse->C & 255);
	cube = parse_to_cube(parse);
	if (!cube)
		return (1);
	cube_error(cube);
	// parse_error(cube);
    // null_cube(&cube);
    return (0);
}
