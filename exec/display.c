/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:43:37 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 12:35:26 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}
