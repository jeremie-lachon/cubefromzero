/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:43:37 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/20 14:04:46 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	givemeplayer(t_cube *cube, int size_w, int size_h)
{
	int	i;
	int	y;

	i = -4;
	while (i != 4)
	{
		y = -4;
		while (y != 4)
		{
			display_pix(cube->mlx->image, \
				(cube->player[PLAYER_X] * size_w) + i, \
				(cube->player[PLAYER_Y] * size_h) + y, 0x0);
			y++;
		}
		i++;
	}
	display_pix(cube->mlx->image, (cube->player[PLAYER_X] * size_w), \
		(cube->player[PLAYER_Y] * size_h), 0x0);
}

static void	frame_setter(t_cube *cube)
{
	if (cube->ray.hit == SPRITE)
	{
		cube->ray.texture = cube->texture[cube->frame];
		cube->ray.adress = (unsigned int *)cube->texture[cube->frame]->adress;
	}
	else
	{
		if (cube->ray.hit == DOOR)
			cube->NSWE = DO;
		cube->ray.texture = cube->texture[cube->NSWE];
		cube->ray.adress = (unsigned int *)cube->texture[cube->NSWE]->adress;
	}
}

static void	draw_pixel_map(int i, t_cube *cube, int pos_y, int pos_x)
{
	if (cube->data.map[pos_y][pos_x] == WALL)
		ft_putpixel(i, cube, 0x1e17fb, 0);
	else if (cube->data.map[pos_y][pos_x] == SPACE)
		ft_putpixel(i, cube, 0xffffff, 0);
	else if (cube->data.map[pos_y][pos_x] == SPRITE)
		ft_putpixel(i, cube, 0x00ff00, 0);
	else if (cube->data.map[pos_y][pos_x] == DOOR)
		ft_putpixel(i, cube, 0xA04000, 0);
	else
		ft_putpixel(i, cube, 0xffffff, 0);
}

static void	minimap_display(t_cube *cube)
{
	int	size_w;
	int	size_h;
	int	i;
	int	pos_y;
	int	pos_x;

	size_w = cube->minimap_w / cube->data.map_w;
	size_h = cube->minimap_h / cube->data.map_h;
	i = 0;
	pos_y = 0;
	pos_x = cube->ray.index / size_w;
	while (i < cube->minimap_h)
	{
		draw_pixel_map(i, cube, pos_y, pos_x);
		i++;
		if (i % size_h == 0 && pos_y < cube->data.map_h - 1)
			pos_y++;
	}
	givemeplayer(cube, size_w, size_h);
}

void	wall_display(t_cube *cube, float dist, float offset)
{
	static float	tetta;
	float			wall_h;
	float			top_pixel;
	float			pixel;

	if (!tetta)
		tetta = tanf(FOV_H * PI / 360) * 2;
	wall_h = dist * tetta;
	pixel = wall_h / WIN_H;
	frame_setter(cube);
	if (wall_h > 1)
	{
		wall_h = (wall_h - 1) / 2;
		top_pixel = wall_h / pixel;
		draw_other(top_pixel, cube);
		draw_wall_other(cube, pixel, offset, top_pixel);
	}
	else
	{
		top_pixel = WIN_H / (cube->ray.texture->pix_h * wall_h);
		wall_h = (1 - wall_h) / 2;
		draw_wall(wall_h, cube, offset);
	}
	if (cube->ray.index < cube->minimap_w)
		minimap_display(cube);
}
