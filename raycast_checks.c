/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:19:55 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/19 16:55:47 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_door(int x, int y, t_cube *cube)
{
	int	plax;
	int	play;

	plax = cube->player[PLAYER_X];
	play = cube->player[PLAYER_Y];
	if (abs(x - plax) <= 1 && abs(y - play) <= 1)
		return (0);
	return (1);
}

int check_wall(float y, float x, t_cube *cube)
{
	int	intx;
	int	inty;

	intx = (int)floorf(x);
	inty = (int)floorf(y);
	if (intx < 0 || inty < 0)
		return (-1);
	if (intx >= cube->data.map_w || inty >= cube->data.map_h)
		return (-1);
	if(cube->data.map[inty][intx] == WALL)
		cube->ray.hit = WALL;
	else if (cube->data.map[inty][intx] == DOOR && check_door(intx, inty, cube))
		cube->ray.hit = DOOR;
	else if (cube->data.map[inty][intx] == SPRITE)
		cube->ray.hit = SPRITE;
	else
		return (1);
	return (0);
}

static float setter(t_cube *cube, float angle, int flag)
{
    if(flag)
    {
        if (angle > 0.5 && angle < 1.5)
        cube->NSWE = WE;
		else
        cube->NSWE = EA;
		return(cube->ray.h_y - floorf(cube->ray.h_y));
    }
    else
    {
        if (angle > 1)
            cube->NSWE = NO;
        else
            cube->NSWE = SO;
        return (cube->ray.v_x - floorf(cube->ray.v_x));
    }
}

void    wall_check(float distxy[2], t_cube *cube, float angle, float cosangled)
{
    float dist;
    float   offset;

	if (distxy[0] == -1  && distxy[1] == -1)
		return ;
	if (distxy[0] == -1.0 || (distxy[1] < distxy[0] && distxy[1] != -1.0))
	{
        offset = setter(cube, angle, 1);
		dist = distxy[1];
		cube->ray.hit = cube->ray.hity;
	}
	else
	{
		dist = distxy[0];
		offset = setter(cube, angle, 0);
		cube->ray.hit = cube->ray.hitx;
	}
	if (cube->NSWE == WE || cube->NSWE == NO)
		offset = 1 - offset;
	wall_display(cube, dist * cosangled, offset);
}
