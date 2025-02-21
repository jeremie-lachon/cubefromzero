/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:59:50 by snek              #+#    #+#             */
/*   Updated: 2025/02/21 09:50:57 by snek             ###   ########.fr       */
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

static void	draw_pixel_map(int i, t_cube *cube, int pos_y, int pos_x)
{	
	(void)i;
	// printf("Y %d X %x\n", pos_y, pos_x);
	if (cube->data.map[pos_y][pos_x] == WALL)
		printf("*");

		// ft_putpixel(i, cube, 0x1e17fb, 0);
	else if (cube->data.map[pos_y][pos_x] == SPACE)
		printf("-");
	// ft_putpixel(i, cube, 0xffffff, 0);
	else if (cube->data.map[pos_y][pos_x] == SPRITE)
		printf(".");
		// ft_putpixel(i, cube, 0x00ff00, 0);
	else if (cube->data.map[pos_y][pos_x] == DOOR)
		printf("+");
		// ft_putpixel(i, cube, 0xA04000, 0);
	else
		printf("/");
		// ft_putpixel(i, cube, 0xffffff, 0);
}

static void	minimap_display(t_cube *cube)
{
	int	size_w;
	int	size_h;
	int	i;
	int	pos_y;
	int	pos_x;
	int	x_place;
	int	y_place;

	x_place = 

	size_w = cube->minimap_w / cube->data.map_w;
	size_h = cube->minimap_h / cube->data.map_h;
	i = 0;
	pos_y = 0;
	pos_x = cube->ray.index / size_w;
	// printf("Ray %d size %d\n",cube->ray.index , size_w );
	// exit(1);
	while (i < cube->minimap_h)
	{
		draw_pixel_map(i, cube, pos_y, pos_x);
		i++;
		if (i % size_h == 0 && pos_y < cube->data.map_h - 1)
		{
			pos_y++;
			printf("\n");
		}
	}
	printf("\n");
	givemeplayer(cube, size_w, size_h);
}
