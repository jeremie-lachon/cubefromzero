/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:59:50 by snek              #+#    #+#             */
/*   Updated: 2025/02/21 12:34:03 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_pixel_map(int x, int y, t_cube *cube, int sprite)
{	
	int	i;
	int	j;

	i = 0;
	if (sprite == SPACE)
		sprite = 0xffffff;
	else if (sprite == WALL)
		sprite = 0x1e17fb;
	else if (sprite == OUT)
		sprite = 0xffffff;
	else if (sprite == DOOR)
		sprite = 0xA04000;
	else
		sprite = 0x00ff00;
	while (i < MM_SIZE)
	{
		j = 0;
		while (j < MM_SIZE)
		{
			display_pix(cube->mlx->image, x + i, y + j, sprite);
			j++;
		}
		i++;
	}
}

void	minimap_display(t_cube *cube)
{
	int	i;
	int	j;
	int	x_place;
	int	y_place;
	int	sprite;
	int	x;
	int	y;


	x_place = (int)cube->player[PLAYER_X] - 2;
	y_place = (int)cube->player[PLAYER_Y] - 2;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			x = x_place + i;
			y = y_place + j;	
			if (x < 0 || x >= cube->data.map_w)
				sprite = OUT;
			else if (y < 0 || y >= cube->data.map_h)
				sprite = OUT;
			else
				sprite = cube->data.map[y][x];
			draw_pixel_map(i * MM_SIZE, j * MM_SIZE, cube, sprite);
			j++;
		}
		i++;
	}
	i = MM_SIZE * 4;
	while (i < MM_SIZE * 5)
	{
		j = MM_SIZE * 4;
		while (j < MM_SIZE * 5)
		{
			display_pix(cube->mlx->image, i, j, 0);
			j++;
		}
		i++;
	}
}
