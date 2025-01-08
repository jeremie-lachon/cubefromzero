/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:44 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/07 23:28:45 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_min(float x, float y)
{
    if (x > y)
        return (y);
    return (x);
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
	if(cube->data.map[inty][intx] == '1')
		return (0);
	return (1);
}

float find_y_ray(t_cube *cube, float angle, float fixed_angle)
{
	float   delta;
	float   move_x;
	float   wall_y;
	int		check;

	delta = cube->player.y - fixed_angle * cube->player.x;
	if(angle < 0.5 || angle > 1.5)
	{
		move_x = floorf(cube->player.x);
		wall_y = fixed_angle * move_x + delta;
		check = check_wall(wall_y, move_x - 1, cube);
		while (check == 1)
		{
			move_x -= 1.0;
			wall_y = fixed_angle * move_x + delta;
			check = check_wall(wall_y, move_x - 1, cube);
		}
	}
	else
	{
		move_x = ceilf(cube->player.x);
		wall_y = fixed_angle * move_x + delta; 
		check = check_wall(wall_y, move_x, cube);
		while (check == 1)
		{
			move_x += 1.0;
			wall_y = fixed_angle * move_x + delta; 
			check = check_wall(wall_y, move_x, cube);
		}
	}
	if (check == -1)
		return (-1.0);
	cube->ray.h_x = move_x;
	if (angle < 0.5 || angle > 1.5)
		cube->ray.h_x -= 1;
	cube->ray.h_y = wall_y;
	return (sqrt(powf(wall_y - cube->player.y, 2) + powf(move_x - cube->player.x, 2)));    
}

float find_x_ray(t_cube *cube, float angle, float fixed_angle)
{
    float   delta;
    float   move_y;
    float   wall_x;
	int		check;

	delta = cube->player.x - cube->player.y / fixed_angle;
	if(angle > 1)
	{
		move_y = floorf(cube->player.y);
		wall_x = delta + move_y / fixed_angle;  
		check = check_wall(move_y - 1, wall_x, cube);
		while (check == 1)
		{
			move_y -= 1.0;
			wall_x = delta + move_y / fixed_angle; 
			check = check_wall(move_y - 1, wall_x, cube);
		}
	}
	else
    {
        move_y = ceilf(cube->player.y);
        wall_x = delta + move_y / fixed_angle; 
		check = check_wall(move_y, wall_x, cube);
		while (check == 1)
        {
            move_y += 1.0;
            wall_x = delta + move_y / fixed_angle; 
			check = check_wall(move_y, wall_x, cube);
        }
    }
	if (check == -1)
		return (-1.0);
    cube->ray.v_y = move_y;
	if (angle > 1)
		cube->ray.v_y -= 1;
    cube->ray.v_x = wall_x;
    return (sqrt(powf(wall_x - cube->player.x, 2) + powf(move_y - cube->player.y, 2)));    
}

float fix_angle(float angle)
{
    while (angle > 2)
        angle -= 2;
    while (angle < 0)
        angle += 2;
    return (angle);
}

void wall_display(t_cube *cube, float dist)
{
	static float tetta;

	if(!tetta)
		tetta = tanf(FOV_H * PI / 180);
}
void wall_check(float dist_x, float dist_y, t_cube *cube, float angle)
{
	int	texture;
	float dist;
    float x;
    float y;
	if (dist_x == -1  && dist_y == -1)
		printf("ERRRRRR\n");
	if (dist_x == -1.0 || (dist_y < dist_x && dist_y != -1.0))
	{
		x = cube->ray.h_x;
		y = cube->ray.h_y;
		if (angle > 0.5 && angle < 1.5)
		{
			texture = west;
		}
		else
			texture = east;
		dist = dist_y;
	}
	else
	{
		dist = dist_x;
		x = cube->ray.v_x;
		y = cube->ray.v_y;
		if (angle > 1)
		{
			texture = north;
		}	
		else
			texture = south;
	}
	wall_display(cube, dist); 

    printf("angle %f dist_X :%f: dist_Y :%f: X1 :%f: Y1 :%f:\n", angle, dist_x, dist_y, x, y);
}

void raycasting(t_cube *cube)
{
    float fixed_angle;
    int i;
    static float pov_h;
    float angle;

    if(!pov_h)
	{
        pov_h = (float)FOV_W / (float)WIN_W;
		pov_h = pov_h / 180;
	}
	i = -1;
    angle = fix_angle(cube->player.angle - (FOV_W / 360));
    while(++i < WIN_W)
    {
        if (angle > 1)
		{
			if (angle < 1.5)
				fixed_angle = tanf((angle - 1) * -PI);
			else
				fixed_angle = tanf((2 - angle) * PI);
		}
		else
		{
			if (angle > 0.5)
				fixed_angle = tanf((1 - angle) * PI);
			else
				fixed_angle = tanf(angle * -PI);
		}
        angle = fix_angle(angle + pov_h);
        wall_check(find_x_ray(cube, angle,fixed_angle), find_y_ray(cube, angle,fixed_angle), cube, angle);
    }
Okey donc if dist_x cest north south et dist_y cest east_wst ?

ok donc une fois dedans 

faudra quon les departage....


}