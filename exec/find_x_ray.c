/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_x_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:32:06 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/20 14:10:30 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_find_x
{
	float	delta;
	float	move_y;
	float	wall_x;
	int		check;
}	t_find_x;

void	find_x_over(t_cube *cube, t_find_x *find, float fixed_angle)
{
	find->move_y = floorf(cube->player[PLAYER_Y]);
	find->wall_x = find->delta + find->move_y / fixed_angle;
	find->check = check_wall(find->move_y - 1, find->wall_x, cube);
	while (find->check == 1)
	{
		find->move_y -= 1.0;
		find->wall_x = find->delta + find->move_y / fixed_angle;
		find->check = check_wall(find->move_y - 1, find->wall_x, cube);
	}
}

void	find_x_else(t_cube *cube, t_find_x *find, float fixed_angle)
{
	find->move_y = ceilf(cube->player[PLAYER_Y]);
	find->wall_x = find->delta + find->move_y / fixed_angle;
	find->check = check_wall(find->move_y, find->wall_x, cube);
	while (find->check == 1)
	{
		find->move_y += 1.0;
		find->wall_x = find->delta + find->move_y / fixed_angle;
		find->check = check_wall(find->move_y, find->wall_x, cube);
	}
}

float	find_x_ray(t_cube *cube, float angle, float fixed_angle)
{
	t_find_x	find;

	find.delta = cube->player[PLAYER_X] - cube->player[PLAYER_Y] / fixed_angle;
	if (angle > 1)
	{
		find_x_over(cube, &find, fixed_angle);
	}
	else
	{
		find_x_else(cube, &find, fixed_angle);
	}
	if (find.check == -1)
		return (-1.0);
	cube->ray.v_y = find.move_y;
	if (angle > 1)
		cube->ray.v_y -= 1;
	cube->ray.v_x = find.wall_x;
	cube->ray.hitx = cube->ray.hit;
	return (sqrt(powf(find.wall_x - cube->player[PLAYER_X], 2) + \
	powf(find.move_y - cube->player[PLAYER_Y], 2)));
}
