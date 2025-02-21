/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:44 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 11:57:35 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycasting(t_cube *cube)
{
    float fixed_angle[2];
    float angle;
	float temp[2];
	cube->ray.index = 0;
    angle = fix_angle(cube->player[ANGLE] - FOV_DEGREE);
    while(cube->ray.index < WIN_W)
    {
        float aux_var;
        if (cube->ray.index < HALF_WIDTH)
        {
            aux_var = atanf((HALF_WIDTH - (float)cube->ray.index) / ADJACENT);
            angle = FOV_DEGREE * PI - aux_var;
            angle = fix_angle(cube->player[ANGLE] - FOV_DEGREE +  angle / PI);
        }
        else
        {
            aux_var = atanf(((float)cube->ray.index - HALF_WIDTH) / ADJACENT);
            angle = fix_angle(cube->player[ANGLE] + aux_var / PI);
        }
        fixed_angle[1] = cosf(aux_var);
        if (angle > 1)
        {
            if (angle < 1.5)
                fixed_angle[0] = tanf((angle - 1.F) * -PI);
            else
                fixed_angle[0] = tanf((2.F - angle) * PI);
        }
        else
        {
            if (angle > 0.5)
                fixed_angle[0] = tanf((1 - angle) * PI);
            else
                fixed_angle[0] = tanf(angle * -PI);
        }
		temp[0] = find_x_ray(cube, angle,fixed_angle[0]);
		temp[1] = find_y_ray(cube, angle,fixed_angle[0]);
        wall_check(temp, cube, angle, fixed_angle[1]);
        cube->ray.index++;
    }
	minimap_display(cube);
}