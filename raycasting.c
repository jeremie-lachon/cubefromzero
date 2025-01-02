/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:44 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/02 19:58:52 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_min(float x, float y)
{
    if (x > y)
        return (y);
    return (x);
}

float find_y_ray(t_cube *cube, float angle)
{
    float   delta;
    float   fixed_angle;
    float   move_x;
    float   wall_y;


    delta = fixed_angle * cube->player.x + cube->player.y;
    if(angle < 0.5 || angle > 1.5)
    {
        move_x = floorf(cube->player.x);
        wall_y = fixed_angle * move_x - delta; 
        while (check_wall(wall_y, move_x, cube))
        {
            move_x -= 1.0;
            wall_y = fixed_angle * move_x - delta; 
        }
    }
    else
    {
        move_x = ceilf(cube->player.x);
        wall_y = fixed_angle * move_x - delta; 
        while (check_wall(wall_y, move_x, cube))
        {
            move_x += 1.0;
            wall_y = fixed_angle * move_x - delta; 
        }
    }
    cube->ray.h_x = move_x;
    cube->ray.h_y = wall_y;
    return (sqrt(powf(wall_y - cube->player.y, 2) + powf(move_x - cube->player.x, 2)));    
}

float find_x_ray(t_cube *cube, float angle, float fixed_angle)
{
    float   delta;
    float   move_x;
    float   wall_y;
    

    delta = cube->player.x - cube->player.y / fixed_angle;
    if(angle > 1)
    {
        move_x = floorf(cube->player.y);
        wall_y = delta + move_x / fixed_angle;  
        while (check_wall(wall_y, move_x, cube))
        {
            move_x -= 1.0;
            wall_y = delta + move_x / fixed_angle; 
        }
    }
    else
    {
        move_x = ceilf(cube->player.y);
        wall_y = delta + move_x / fixed_angle; 
        while (check_wall(wall_y, move_x, cube))
        {
            move_x += 1.0;
            wall_y = delta + move_x / fixed_angle; 
        }
    }
    cube->ray.v_y = move_x;
    cube->ray.v_x = wall_y;
    return (sqrt(powf(wall_y - cube->player.y, 2) + powf(move_x - cube->player.x, 2)));    
}

float fix_angle(float angle)
{
    while (angle > 2)
        angle -= 2;
    while (angle < 0)
        angle += 2;
    return (angle);
}

void raycasting(t_cube *cube)
{
    float fixed_angle;
    int i;
    static float pov_h;
    float angle;
    float distance_x;
    float distance_y;

    if(!pov_h)
        pov_h = FOV_W / WIN_W;
    i = -1;
    angle = fix_angle(cube->player.angle - pov_h / 2);
    while(++i < WIN_W)
    {
        if (angle > 1)
            fixed_angle = tanf(ft_min(2 - angle, angle - 1) * PI);
        else
            fixed_angle = tanf(ft_min(1 - angle, angle) * PI);
        angle = fix_angle(angle + pov_h);
        distance_x = find_x_ray(cube, ,fixed_angle); 
    }
}