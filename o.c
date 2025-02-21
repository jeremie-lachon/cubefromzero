/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:56:48 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 14:18:40 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cub3d.h"

int function(char *s)
{
	int i;
	int ret;
	int tmp;
	ret = 0;
	i = 1;
	if (skip(s, &i, 0) || !s[i])
		return (-1);
	tmp = ft_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret = tmp << 16;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = ft_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret |= tmp << 8;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = ft_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret |= tmp;
	return (ret);
}
// int parse_filler2(char *buf, t_parse *cube)
// {
// 	char *tmp;

// 	if (!buf)
// 		return (1);
// 	if (*buf == '\n')
// 		return (free(buf), 0);
// 	tmp = ft_strchr(buf, '\n');
// 	if (!tmp)
// 		return (1);
// 	if (!strncmp("NO ", buf, 3) && !cube->textures[NO])
// 		cube->textures[NO] = ft_strtrim(ft_substr(buf, 	(buf), tmp - buf - 3), " \t\v\f\r\n");
// 	else if (!strncmp("WE ", buf, 3) && !cube->textures[WE])
// 		cube->textures[WE] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
// 	else if (!strncmp("SO ", buf, 3) && !cube->textures[SO])
// 		cube->textures[SO] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
// 	else if (!strncmp("EA ", buf, 3) && !cube->textures[EA])
// 		cube->textures[EA] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
// 	else if (!strncmp("F ", buf, 2) && cube->F == -1)
// 		cube->F = function(buf);
// 	else if (!strncmp("C ", buf, 2) && cube->C == -1)
// 		cube->C = function(buf);
// 	else if (!strncmp("DO ", buf, 3) && !cube->textures[DO])
// 		cube->textures[DO] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
// 	else if (!strncmp("SP ", buf, 3) && !cube->textures[SP])
// 		cube->textures[SP] = ft_strtrim(ft_substr(buf, settings_split(buf), tmp - buf - 3), " \t\v\f\r\n");
// 	else
// 		return (2);
// 	return (free(buf), 0);
// }

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
			parse->map[i][j] = OUT;
		else
			return (printf("Error\nIncorrect map information\n"), 1);
		j++;
	}
	while (j < parse->width)
		parse->map[i][j++] = OUT;
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



int mapcheckandstock(t_list *list, t_parse *map)
{
	int i;
	t_list *tmp;

	map->height = listsize(list);
	map->map = ft_calloc(sizeof(int *), map->height);
	if (!map->map)
		return (perror("Error\n"), listfree(list), 1);
	map->width = maxsize(list);
	i = 0;
	tmp = list;
	while (i < map->height)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width);
		if (!map->map[i])
			return (perror("Error\n"), listfree(list), intfree(&map->map, i), 1);
		if (fillmap(tmp, map, i))
			return (listfree(list), intfree(&map->map, i + 1), 1);
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
		return (printf("Error\nInformation after map\n"), free(str), listfree(list), 1);
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
		return (printf("Error\nMissing information\n"), gnlfree(fd), 1);
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

	parse = ft_calloc(sizeof(t_parse), 1);
	if (!parse)
		return (perror("Error\n"), NULL);
	parse->textures = ft_calloc(sizeof(char *), 6);
	if (!parse->textures)
		return (perror("Error\n"), free(parse), NULL);
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
		return (perror("Error\n"), NULL);
	while (i < 5)
	{
		cube->texture[i] = ft_calloc(sizeof(t_img_data), 1);
		if (!cube->texture[i++])
			return (perror("Error\n"), freecubetext(cube), free(cube), NULL);
	}
	return (cube);
}

t_cube *parse_to_cube(t_parse *parse, t_mlx *mlx)
{
	t_cube *cube;

	cube = ft_cube_init();
	if (!cube)
		return (parsefree(parse), ft_clear_display(mlx), NULL);
	cube->mlx = mlx;
	cube->data.map = parse->map;
	parse->map = 0;
	cube->data.map_w = parse->width;
	cube->data.map_h = parse->height;
	// printf("parse->height %d parse->width %d\n", parse->height, parse->width);
	cube->data.FC[0] = parse->F;
	cube->data.FC[1] = parse->C;
	cube->player[PLAYER_X] = parse->player[PLAYER_X];
	cube->player[PLAYER_Y] = parse->player[PLAYER_Y];
	cube->player[ANGLE] = parse->player[ANGLE];
	if (fillsides(cube, parse, cube->mlx))
		return (printf("Error\nProblem converting wall/door images to mlx_img"), free_cube(cube), parsefree(parse), NULL);
	if (fillsprite(parse, cube, cube->mlx))
		return (freetexts(cube), printf("Error\nProblem converting sprite images to mlx_img"), free_cube(cube), parsefree(parse), NULL);
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


void	display_pix2(t_img_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->adress + (y * img->size + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

void	ft_putpixel2(int ray, int i, t_cube *cube, int flag)
{
	if (flag)
	{
		if (ray < 0 || ray >= WIN_W || \
			i > WIN_H || i < 0)
			return ;
		if (ray <= cube->minimap_w && i <= cube->minimap_h)
			return ;
	}
	display_pix(cube->mlx->image, ray, i, 0xea0000);
}

void draw_map_line(t_cube *cube, int x)
{
	int y;

	y = 0;
	while (y < cube->minimap_h)
	{
		ft_putpixel2(x, y, cube, 0);
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