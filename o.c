/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:56:48 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/19 17:06:22 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cube.h"
#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// settings check 0
// map      check 1

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

char *ft_strchr(const char *s, int c)
{
	char *ptr;
	int i;

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

char *ft_substr(char const *s, int start, int len)
{
	int i;
	int j;
	char *copy;

	if (start < 0)
		return (0);
	if (start > (int)strlen(s))
		return (calloc(1, 1));
	if (len + start <= (int)strlen(s))
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
		if (s[*i] == ',')
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
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret |= tmp << 8;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret |= tmp;
	return (ret);
}
// Trim

void *ft_calloc(size_t nmemb, size_t size)
{
	size_t i;
	unsigned char *new;

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

static int check_char(const char *set, char c)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static char *strmalloc(int *tab)
{
	char *new;

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
char *ft_strtrim(char *s1, char const *set)
{
	char *new;
	int tab[3];

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

int parse_filler2(char *buf, t_parse *cube)
{
	char *tmp;

	if (!buf)
		return (1);
	if (*buf == '\n')
		return (free(buf), 0);
	tmp = ft_strchr(buf, '\n');
	if (!tmp)
		return (1);
	if (!strncmp("NO ", buf, 3) && !cube->textures[NO])
		cube->textures[NO] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
	else if (!strncmp("WE ", buf, 3) && !cube->textures[WE])
		cube->textures[WE] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
	else if (!strncmp("SO ", buf, 3) && !cube->textures[SO])
		cube->textures[SO] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
	else if (!strncmp("EA ", buf, 3) && !cube->textures[EA])
		cube->textures[EA] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
	else if (!strncmp("F ", buf, 2) && cube->F == -1)
		cube->F = function(buf);
	else if (!strncmp("C ", buf, 2) && cube->C == -1)
		cube->C = function(buf);
	else if (!strncmp("DO ", buf, 3) && !cube->textures[DO])
		cube->textures[DO] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
	else if (!strncmp("SP ", buf, 3) && !cube->textures[SP])
		cube->textures[SP] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
	else
		return (2);
	return (free(buf), 0);
}

void NSEW(int i, int j, char *str, t_parse *parse)
{
	parse->map[i][j] = SPACE;
	parse->player[PLAYER_Y] = i + 0.5;
	parse->player[PLAYER_X] = j + 0.5;
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

int fillmap(t_list *node, t_parse *parse, int i)
{
	int j;
	char *str;

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
			NSEW(i, j, str, parse);
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

int checksides(t_parse *parse, int i, int j)
{
	if (!i || i + 1 == parse->height)
		return (1);
	if (!j || j + 1 == parse->width)
		return (1);
	if (parse->map[i - 1][j] == OUT)
		return (1);
	if (parse->map[i][j - 1] == OUT)
		return (1);
	if (parse->map[i][j + 1] == OUT)
		return (1);
	if (parse->map[i + 1][j] == OUT)
		return (1);
	return (0);
}

void printmap(t_parse *parse)
{
	int i;
	int j;
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

int check_final_elements(t_parse *parse)
{
	if (!parse->textures[NO] || !parse->textures[EA] || !parse->textures[WE])
		return (1);
	if (!parse->textures[SO] || parse->C == -1 || parse->F == -1)
		return (1);
	return (0);
}

int check_elements(t_parse *parse)
{
	int spritedoor[2];
	int i;
	int j;

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

int checkmap(t_parse *parse)
{
	int i;
	int j;

	i = 0;
	printmap(parse);
	while (i < parse->height)
	{
		j = 0;
		while (j < parse->width)
		{
			if (parse->map[i][j] == SPACE || parse->map[i][j] == DOOR)
				if (checksides(parse, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (check_elements(parse));
}

int mapcheckandstock(t_list *list, t_parse *map)
{
	int i;
	t_list *tmp;

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

char *remove_end(char *str)
{
	char *tmp;

	tmp = strchr(str, '\n');
	if (!tmp)
		return (strdup(str));
	tmp = ft_substr(str, 0, tmp - str);
	return (tmp);
}


int mapper(int fd, t_parse *parse, char *str)
{
	t_list *list;
	t_list *new;

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
			break;
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

int parse_filler(int fd, t_parse *cube)
{
	char *buff;
	int check;

	buff = custom_read(fd, 0);
	check = parse_filler2(buff, cube);
	while (!check)
	{
		buff = custom_read(fd, 1);
		check = parse_filler2(buff, cube);
	}
	if (check == 1)
		return (gnlfree(fd), 1);
	if (mapper(fd, cube, buff))
		return (gnlfree(fd), 1);
	return (gnlfree(fd), 0);
}

int cub_check(char *str)
{
	int i;

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

t_parse *parseinit(void)
{
	t_parse *parse;

	parse = calloc(sizeof(t_parse), 1);
	if (!parse)
		return (0);
	parse->textures = calloc(sizeof(char *), 6);
	if (!parse->textures)
		return (free(parse), NULL);
	parse->C = -1;
	parse->F = -1;
	return (parse);
}

void freetexts(t_cube *cube)
{
	int j;

	j = 0;
	while (j < 6)
	{
		if (j < 5 && cube->texture[j]->img_ptr)
			mlx_destroy_image(cube->mlx->mlx, cube->texture[j]->img_ptr);
		free(cube->texture[j]);

		cube->texture[j++] = 0;
	}
}

static int imgstruct(t_cube *cube, int num, t_mlx *mlx, t_parse *parse)
{
	cube->texture[num]->img_ptr = mlx_xpm_file_to_image(mlx->mlx, parse->textures[num], &cube->texture[num]->pix_w, &cube->texture[num]->pix_h);
	if (!cube->texture[num]->img_ptr)
		return (freetexts(cube), 1);
	cube->texture[num]->adress = mlx_get_data_addr(cube->texture[num]->img_ptr, &cube->texture[num]->bpp, &cube->texture[num]->size, &cube->texture[num]->endl);
	if (!cube->texture[num]->adress)
		return (freetexts(cube), 1);
	return (0);
}

int fillsides(t_cube *cube, t_parse *parse, t_mlx *mlx)
{
	if (imgstruct(cube, NO, mlx, parse))
		return (1);
	if (imgstruct(cube, WE, mlx, parse))
		return (1);
	if (imgstruct(cube, SO, mlx, parse))
		return (1);
	if (imgstruct(cube, EA, mlx, parse))
		return (1);
	if (parse->textures[DO] && imgstruct(cube, DO, mlx, parse))
		return (1);
	return (0);
}

static void freesprite(t_img_data **sprite, int n, t_mlx *mlx)
{
	int j;

	if (!sprite)
		return;
	j = 0;
	while (j < n)
	{
		if (sprite[j])
			mlx_destroy_image(mlx->mlx, sprite[j++]->img_ptr);
	}
}

int fillsprite(t_parse *parse, t_cube *cube, t_mlx *mlx)
{
	int n;
	char **all;

	if (!parse->textures[SP])
		return (0);
	all = ft_split(parse->textures[SP], ' ');
	if (!all)
		return (1);
	n = 0;
	while (all[n])
		n++;
	cube->sprite = ft_calloc(n, sizeof(t_img_data *));
	if (!cube->sprite)
		return (ft_freesplit(all, n), 1);
	cube->nsprite = n;
	n = 0;
	while (n < cube->nsprite)
	{
		cube->sprite[n] = ft_calloc(sizeof(t_img_data), 1);
		if (!cube->sprite[n])
			return (freesprite(cube->sprite, n, mlx), ft_freesplit(all, n), 1);
		cube->sprite[n]->img_ptr = mlx_xpm_file_to_image(mlx->mlx, all[n], &cube->sprite[n]->pix_w, &cube->sprite[n]->pix_h);
		if (!cube->sprite[n]->img_ptr)
			return (freesprite(cube->sprite, n, mlx), ft_freesplit(all, n), 1);
		cube->sprite[n]->adress = mlx_get_data_addr(cube->sprite[n]->img_ptr, &cube->sprite[n]->bpp, &cube->sprite[n]->size, &cube->sprite[n]->endl);
		if (!cube->sprite[n]->adress)
			return (freesprite(cube->sprite, n, mlx), ft_freesplit(all, n), 1);
		n++;
	}
	return (ft_freesplit(all, n), 0);
}

static void freecubetext(t_cube *cube)
{
	int i;

	i = 0;
	while (i < 5)
	{
		free(cube->texture[i]);
		cube->texture[i++] = 0;
	}
}

static t_cube *ft_cube_init(void)
{
	t_cube *cube;
	int i;

	i = 0;
	cube = ft_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (0);
	while (i < 5)
	{
		cube->texture[i] = ft_calloc(sizeof(t_img_data), 1);
		if (!cube->texture[i++])
			return (freecubetext(cube), free(cube), NULL);
	}
	return (cube);
}

t_cube *parse_to_cube(t_parse *parse, t_mlx *mlx)
{
	t_cube *cube;

	cube = ft_cube_init();
	if (!cube)
		return (perror("Error\n"), parsefree(parse), ft_clear_display(mlx), NULL);
	cube->mlx = mlx;
	cube->data.map = parse->map;
	parse->map = 0;
	cube->data.map_w = parse->width;
	cube->data.map_h = parse->height;
	cube->data.FC[0] = parse->F;
	cube->data.FC[1] = parse->C;
	cube->player[PLAYER_X] = parse->player[PLAYER_X];
	cube->player[PLAYER_Y] = parse->player[PLAYER_Y];
	cube->player[ANGLE] = parse->player[ANGLE];
	if (fillsides(cube, parse, cube->mlx))
		return (perror("Error\n"), free_cube(cube), parsefree(parse), NULL);
	if (fillsprite(parse, cube, cube->mlx))
		return (freetexts(cube), perror("Error\n"), free_cube(cube), parsefree(parse), NULL);
	return (parsefree(parse), cube);
}

static t_mlx *ft_mlx_init(void)
{
	t_mlx *mlx;

	mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!mlx)
		return (NULL);
	mlx->img1 = ft_calloc(sizeof(t_img_data), 1);
	if (!mlx->img1)
		return (free(mlx), NULL);
	mlx->img2 = ft_calloc(sizeof(t_img_data), 1);
	if (!mlx->img2)
		return (free(mlx->img1), free(mlx), NULL);
	return (mlx);
}

int ft_mlx_start(t_mlx **mlx_address)
{
	t_mlx *mlx;

	mlx = ft_mlx_init();
	if (!mlx)
		return (1);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cube");
	if (!mlx->win)
		return (mlx_destroy_display(mlx->mlx), 1);
	mlx->img1->img_ptr = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (!mlx->img1)
		return (mlx_destroy_window(mlx->mlx, mlx->win), mlx_destroy_display(mlx->mlx), 1);
	mlx->img1->adress = mlx_get_data_addr(mlx->img1->img_ptr, &mlx->img1->bpp, &mlx->img1->size, &mlx->img1->endl);
	mlx->img2->img_ptr = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (!mlx->img2)
		return (mlx_destroy_image(mlx->mlx, mlx->img1->img_ptr), mlx_destroy_window(mlx->mlx, mlx->win), mlx_destroy_display(mlx->mlx), 1);
	mlx->img2->adress = mlx_get_data_addr(mlx->img2->img_ptr, &mlx->img2->bpp, &mlx->img2->size, &mlx->img2->endl);
	*mlx_address = mlx;
	return (0);
}

void mouse_rotation(t_cube *cube)
{
	mlx_mouse_get_pos(cube->mlx->mlx, cube->mlx->win, &cube->mouse_x, &cube->mouse_y);
	if (cube->mouse_x < 0 || cube->mouse_x > WIN_W || cube->mouse_y < 0 || cube->mouse_y > WIN_H)
		cube->mouse_x = HALF_WIDTH;
	if (cube->mouse_x > HALF_WIDTH + 150)
		cube->input[MOUSE_LEFT] = 1;
	else
		cube->input[MOUSE_LEFT] = 0;
	if (cube->mouse_x < HALF_WIDTH - 150)
		cube->input[MOUSE_RIGHT] = 1;
	else
		cube->input[MOUSE_RIGHT] = 0;
}

void draw_map_line(t_cube *cube, int x)
{
	int y;

	y = 0;
	while (y < cube->minimap_h)
	{
		ft_putpixel(x, y, cube, 0xea0000, 0);
		y++;
	}
}
void draw_minimap(t_cube *cube)
{
	int i;

	i = 0;
	while (i < cube->minimap_w)
	{
		draw_map_line(cube, i);
		i++;
	}
}

int loop_render(t_cube *cube)
{
	static int i;
	struct timeval time;

	if (!i)
	{
		cube->mlx->image = cube->mlx->img1;
		i++;
	}
	else
	{
		cube->mlx->image = cube->mlx->img2;
		i--;
	}
	gettimeofday(&time, NULL);
	cube->frame = time.tv_sec % 4;
	cube->player[ANGLE] = fix_angle(cube->player[ANGLE]);
	printf("angle %f; x %f; y %f;\n", cube->player[ANGLE], cube->player[PLAYER_X], cube->player[PLAYER_Y]);
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx->mlx, cube->mlx->win, cube->mlx->image->img_ptr, 0, 0);
	moving(cube);
	mouse_rotation(cube);
	return (0);
}

int main(int ac, char **av)
{
	t_parse *parse;
	t_cube *cube;
	t_mlx *mlx;
	int fd;

	if (ac != 2)
		return (write(1, "Error\nWrong number of arguments.\n", 33), 1);
	if (cub_check(av[1]))
		return (write(1, "Error\nMap is not using .cub extension.\n", 39), 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 1);
	parse = parseinit();
	if (!parse || parse_filler(fd, parse))
		return (perror("Error\n"), parsefree(parse), 1);
	mlx = 0;
	if (ft_mlx_start(&mlx))
		return (perror("Error\n"), free(mlx), parsefree(parse), 1);
	cube = parse_to_cube(parse, mlx);
	if (!cube)
		return (1);

	int h, w;
	// Partie size map
	if (cube->data.map_w > cube->data.map_h)
	{
		h = 20;
		w = 10;
	}
	else if (cube->data.map_w < cube->data.map_h)
	{
		w = 20;
		h = 10;
	}
	else
	{
		w = 20;
		h = 10;
	}
	cube->minimap_w = (cube->data.map_w) * w;
	cube->minimap_h = cube->data.map_h * h;

	mlx_hook(cube->mlx->win, KeyPress, KeyPressMask, &key_press, cube);
	mlx_hook(cube->mlx->win, KeyRelease, KeyReleaseMask, &key_release, cube);
	mlx_hook(cube->mlx->win, 17, 0, &escape, cube);
	mlx_loop_hook(cube->mlx->mlx, &loop_render, cube);

	mlx_loop(cube->mlx->mlx);

	// printf("NO:%s:, SO:%s:, EA:%s:, WE:%s:\n", parse->textures[NO], parse->textures[SO], parse->textures[EA], parse->textures[WE]);
	// printf("F %d:%d:%d C %d:%d:%d \n", (parse->F >> 16) & 0xFF, (parse->F >> 8) & 0xFF, parse->F & 0xFF, parse->C >> 16 & 255, parse->C >> 8 & 255, parse->C & 255);
	free_cube(cube);
	return (0);
}
