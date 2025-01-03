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

int check_wall(float y, float x, t_cube *cube, int entry)
{
    printf("From %d X :%d: Y :%d:\n",entry, (int)floor(x), (int)floor(y));
    sleep(1);
    if ((int)floor(x) < 0 || (int)floor(y) < 0)
        return (1);
    if ((int)floor(x) >= cube->data.map_w || (int)floor(y) >= cube->data.map_h)
        return (1);
    if(cube->data.map[(int)floor(x)][(int)floor(y)] == '1')
        return (0);
    return (1);
}
float find_y_ray(t_cube *cube, float angle, float fixed_angle)
{
    float   delta;
    float   move_x;
    float   wall_y;


    delta = fixed_angle * cube->player.x + cube->player.y;
    if(angle < 0.5 || angle > 1.5)
    {
        move_x = floorf(cube->player.x);
        // pb here and wall_y calc \/
        wall_y = fixed_angle * move_x + delta; 
        printf("WALL Y %f\n", wall_y);

        while (check_wall(wall_y, move_x, cube, 1))
        {
            move_x -= 1.0;
            wall_y = fixed_angle * move_x - delta; 
        }
    }
    else
    {
        move_x = ceilf(cube->player.x);
        wall_y = fixed_angle * move_x - delta; 
        while (check_wall(wall_y, move_x, cube, 1))
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
        while (check_wall(move_x, wall_y, cube, 2))
        {
            move_x -= 1.0;
            wall_y = delta + move_x / fixed_angle; 
        }
    }
    else
    {
        move_x = ceilf(cube->player.y);
        wall_y = delta + move_x / fixed_angle; 
        while (check_wall(move_x, wall_y, cube, 2))
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

void wall_check(float dist_x, float dist_y, t_cube *cube)
{
    // float x;
    // float y;

    printf("dist_X :%f: dist_Y :%f: X1 :%f: Y1 :%f:  X2 :%f: Y2 :%f:\n", dist_x, dist_y, cube->ray.v_x,cube->ray.v_y,cube->ray.h_x,cube->ray.h_y);
}

void raycasting(t_cube *cube)
{
    float fixed_angle;
    int i;
    static float pov_h;
    float angle;

    if(!pov_h)
        pov_h = (float)FOV_W / (float)WIN_W;
    i = -1;
    angle = fix_angle(cube->player.angle - pov_h / 2);
    while(++i < WIN_W)
    {
        if (angle > 1)
            fixed_angle = tanf(ft_min(2 - angle, angle - 1) * PI);
        else
            fixed_angle = tanf(ft_min(1 - angle, angle) * PI);
        angle = fix_angle(angle + pov_h);
        printf("fixedanvle angle %f %f %f\n", fixed_angle , angle, tanf(ft_min(2 -angle, angle -1) * PI));
        wall_check(find_x_ray(cube, angle,fixed_angle), find_y_ray(cube, angle,fixed_angle), cube);
    }
}