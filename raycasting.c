/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:44 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/08 19:48:57 by jla-chon         ###   ########.fr       */
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

void display_pix(t_img_data *img, int x, int y, int color)
{
    char *dest;
	// printf("JE RENTRE LA\n");
    dest = img->adress + (y * img->size + x  * (img->bpp / 8));
    *(unsigned int *)dest = color;
}

void ft_putpixel(int ray, int i, t_cube *cube, int color)
{
    if(ray < 0 || ray >= WIN_W || i > WIN_H || i < 0)
        return ;
    display_pix(&cube->img, ray, i, color);
    
}

void draw_wall(float top_pixel, t_cube *cube, float bot)
{
	int i;
	int k;
	float l;
	unsigned int *adress;
	t_img_data texture;
	// printf("je rentre ici \n");
	// exit(2);
	texture = cube->texture[cube->NSWE];
	adress = cube->texture[cube->NSWE].adress;
	i = 0;
	k = (int)cube->ray.index;
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
		ft_putpixel(cube->ray.index, i, cube, adress[texture.pix_w  * k + (int)floor(l / top_pixel / i)]);
		i++;	
	}
}


void draw_other(float top, float wall, t_cube *cube)
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
        ft_putpixel(cube->ray.index, i, cube, 0x00456465);
		i++;
	}
	while(i < WIN_H)
	{
        ft_putpixel(cube->ray.index, i, cube, cube->data.FC[1]);
		i++;
	}
}

void wall_display(t_cube *cube, float dist)
{
	static float tetta;
	float wall_h;
	float top_pixel;
	float pixel;
	// printf("im in wall display\n");

	if(!tetta)
		tetta = tanf(FOV_H * PI / 360) * 2;
	wall_h = dist * tetta;
	pixel = wall_h / WIN_H;
	if(wall_h > 1)
	{
		wall_h = (wall_h - 1) / 2;
		top_pixel = wall_h / pixel;
		printf("top pixel :%f:\n", top_pixel);
		draw_other(top_pixel, wall_h, cube);
		draw_wall(top_pixel, cube, WIN_H - top_pixel);
	}
	else
	{	
		top_pixel = (cube->texture[cube->NSWE].pix_h * wall_h) / WIN_H;
		wall_h = (1 - wall_h) / 2;
		draw_wall(top_pixel, cube, wall_h / pixel);
		// printf("HELLO\n");
		// top pixel cest le haut du mur qu'on voit
		// wall_h cest la taille du mur 
	}
}

void wall_check(float dist_x, float dist_y, t_cube *cube, float angle)
{
	int	texture;
	float dist;
    float x;
    float y;
	// printf("im in wall check\n");
	if (dist_x == -1  && dist_y == -1)
		printf("ERRRRRR\n");
	if (dist_x == -1.0 || (dist_y < dist_x && dist_y != -1.0))
	{
		x = cube->ray.h_x;
		y = cube->ray.h_y;
		if (angle > 0.5 && angle < 1.5)
		{
			cube->NSWE = WEST;
		}
		else
			cube->NSWE = EAST;
		dist = dist_y;
	}
	else
	{
		dist = dist_x;
		x = cube->ray.v_x;
		y = cube->ray.v_y;
		if (angle > 1)
		{
			cube->NSWE = NORTH;
		}	
		else
			cube->NSWE = SOUTH;
	}
	wall_display(cube, dist); 

    // printf("angle %f dist_X :%f: dist_Y :%f: X1 :%f: Y1 :%f:\n", angle, dist_x, dist_y, x, y);
}

void raycasting(t_cube *cube)
{
    float fixed_angle;
    int i;
    static float pov_h;
    float angle;

    if(!pov_h)
	{
        pov_h = FOV_W / WIN_W;
		pov_h = pov_h / 180.F;
	}
    angle = fix_angle(cube->player.angle - (FOV_W / 360.F));
	cube->ray.index = 0;
	// Ca marche jusque < 612
    while(cube->ray.index < 1000)
    {
        if (angle > 1)
		{
			if (angle < 1.5)
				fixed_angle = tanf((angle - 1.F) * -PI);
			else
				fixed_angle = tanf((2.F - angle) * PI);
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
		cube->ray.index++;
	}
    mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img_ptr, 0, 0);
	// printf("ICI %d %d\n", cube->ray.index, WIN_W);
	// exit(6);
}