/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:44 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/12 06:20:38 by snek             ###   ########.fr       */
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

float	find_y_ray(t_cube *cube, float angle, float fixed_angle)
{
	float	delta;
	float	move_x;
	float	wall_y;
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

float	find_x_ray(t_cube *cube, float angle, float fixed_angle)
{
	float	delta;
	float	move_y;
	float	wall_x;
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

float	fix_angle(float angle)
{
	while (angle > 2)
		angle -= 2;
	while (angle < 0)
		angle += 2;
	return (angle);
}

void display_pix(t_img_data *img, int x, int y, int color)
{
	char *dest;
	// printf("JE RENTRE LA\n");
	dest = img->adress + (y * img->size + x  * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

void ft_putpixel(int ray, int i, t_cube *cube, int color)
{
	if (ray < 0 || ray >= WIN_W || i > WIN_H || i < 0)
		return ;
    display_pix(&cube->img, ray, i, color);
    
}

void draw_wall(float top_pixel, t_cube *cube, float bot, float offset)
{
	int i;
	int k;
	float l;
	unsigned int *adress;
	t_img_data texture;
	texture = cube->texture[cube->NSWE];
	adress = (unsigned int *)cube->texture[cube->NSWE].adress;
	i = 0;
	k = (int)floor(offset * texture.pix_w);
	l = top_pixel;
	i = ceil(top_pixel);
	while(i < bot)
	{

		// Issue vient de ray.index

		l += bot;
		/* Jai swith  (int)floor(l) en  (int)floor(i)
			Et ca marche. Le issue est que "l" ne sert plus a rien ??? Whats going on, HEWO?
			Anyway ca render au moins donc tant mieux
			(int)floor(l /  top_pixel) marche aussi

			Blessed be I, but i aint the smarted of the lords creations
		*/
		// int pre;
		// pre = adress[texture.pix_w  * k + (int)floor(l / top_pixel / i)];
		ft_putpixel(cube->ray.index, i, cube, adress[texture.pix_w  * (int)floor(l / top_pixel / i) + k]);
		// if (pre != adress[texture.pix_w  * k + (int)floor(l / top_pixel / i)])
		// {
		// 	printf("Before %d After %d\n", pre, adress[texture.pix_w  * k + (int)floor(l / top_pixel / i)]);
		// 	sleep(1);
		// }
		i++;
	}
}

void	move_player(t_cube *cube, float angle)
{
	int		map_grid_y;
	int		map_grid_x;
	float	new_x;
	float	new_y;

	angle = angle * PI;
	new_x = (cube->player.x + (cos(angle) / 3));
	new_y = (cube->player.y + (sin(angle) / 3));
	map_grid_x = ((int)new_x);
    
    if(map_grid_x > cube->data.map_w)
    {
        map_grid_x = cube->data.map_w;
    }
    map_grid_y = ((int)new_y);

    if(map_grid_y > cube->data.map_h)
    {   
        map_grid_y = cube->data.map_h;
    }
	if (cube->data.map[map_grid_y][map_grid_x] != '1')
    {
        if(cube->data.map[map_grid_y][(int)cube->player.x] != '1' ||
          cube->data.map[(int)cube->player.y][map_grid_x] != '1')
            {
                cube->player.x = new_x;
                cube->player.y = new_y;
            }
    }
	printf("X :%f: Y :%f: Angle :%f:\n", cube->player.x, cube->player.y, cube->player.angle);

}


void draw_wall_other(t_cube *cube, float pixel, float offset, int i)
{
	int		k;
	float	stat;
	float	l;
	unsigned int *adress;
	t_img_data texture;
	texture = cube->texture[cube->NSWE];
	adress = (unsigned int *)cube->texture[cube->NSWE].adress;
	stat = texture.pix_h * pixel ;
	k = (int)floor(offset * texture.pix_w);
	l = 0;
	while(l < texture.pix_h)
	{
		ft_putpixel(cube->ray.index, i, cube, adress[texture.pix_w  * (int)floor(l) + k]);
		l += stat;
		i++;
	}
}

void draw_other(float top, t_cube *cube)
{
	int i;

	i = 0;
	while(i < top)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->data.FC[0]);
		i++;
	}
	while(i < WIN_H - top)
	{
		ft_putpixel(cube->ray.index, i, cube, 16777215);
		i++;
	}
	while(i < WIN_H)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->data.FC[1]);
		i++;
	}
}

void wall_display(t_cube *cube, float dist, float offset)
{
	static float	tetta;
	float			wall_h;
	float			top_pixel;
	float			pixel;
	// printf("im in wall display\n");

	if(!tetta)
		tetta = tanf(FOV_H * PI / 360) * 2;
	wall_h = dist * tetta;
	pixel = wall_h / WIN_H;
	if(wall_h > 1)
	{
		wall_h = (wall_h - 1) / 2;
		top_pixel = wall_h / pixel;
		// printf("top pixel :%f: of ray %d with offset %f \n", top_pixel, cube->ray.index, offset);
		draw_other(top_pixel, cube);
		draw_wall_other(cube, pixel, offset, top_pixel);
	}
	else
	{
		top_pixel = (cube->texture[cube->NSWE].pix_h * wall_h) / WIN_H;
		wall_h = (1 - wall_h) / 2;
		draw_wall(top_pixel, cube, wall_h / pixel, offset);
		// top pixel cest le haut du mur qu'on voit
		// wall_h cest la taille du mur 
	}
}

void wall_check(float dist_x, float dist_y, t_cube *cube, float angle, float cosangled)
{
	// int	texture;
	float dist;
    float offset;
	// printf("im in wall check\n");
	if (dist_x == -1  && dist_y == -1)
		printf("ERRRRRR\n");
	if (dist_x == -1.0 || (dist_y < dist_x && dist_y != -1.0))
	{
		offset = cube->ray.h_y - floorf(cube->ray.h_y);
		if (angle > 0.5 && angle < 1.5)
			cube->NSWE = WEST;
		else
			cube->NSWE = EAST;
		dist = dist_y;
	}
	else
	{
		dist = dist_x;
		offset = cube->ray.v_x - floorf(cube->ray.v_x);
		if (angle > 1)
			cube->NSWE = NORTH;
		else
			cube->NSWE = SOUTH;
	}
	// printf("angle %f dist_X :%f: dist_Y :%f: X1 :%f: Y1 :%f:\n", angle, dist_x, dist_y, x, y);
	wall_display(cube, dist * cosangled, offset);
}

void raycasting(t_cube *cube)
{
    float fixed_angle[2];
    float angle;

    angle = fix_angle(cube->player.angle - FOV_DEGREE);
    while(cube->ray.index < WIN_W)
    {
        float aux_var;
        if (cube->ray.index < HALF_WIDTH)
        {
            aux_var = atanf((HALF_WIDTH - (float)cube->ray.index) / ADJACENT);
            angle = FOV_DEGREE * PI - aux_var;
            angle = fix_angle(cube->player.angle - FOV_DEGREE +  angle / PI);
        }
        else
        {
            aux_var = atanf(((float)cube->ray.index - HALF_WIDTH) / ADJACENT);
            angle = fix_angle(cube->player.angle + aux_var / PI);
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
        wall_check(find_x_ray(cube, angle,fixed_angle[0]), find_y_ray(cube, angle,fixed_angle[0]), cube, angle, fixed_angle[1]);
        cube->ray.index++;
    }
}