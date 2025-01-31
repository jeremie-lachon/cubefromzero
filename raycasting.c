/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:44 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/31 19:04:36 by snek             ###   ########.fr       */
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
	dest = img->adress + (y * img->size + x  * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

void ft_putpixel(int ray, int i, t_cube *cube, int color, int flag)
{
	if(flag)
	{
		if (ray < 0 || ray >= WIN_W || i > WIN_H || i < 0)
			return ;
		if(ray <= cube->minimap_w && i <= cube->minimap_h)
			return ;
	}
	display_pix(&cube->img, ray, i, color);
}

void draw_wall(float top_pixel, t_cube *cube, float offset)
{
	int i;
	int k;
	float l;
	float scale;
	unsigned int *adress;
	t_img_data texture;
	if(cube->NSWE != NORTH)
	{
		texture = cube->texture[cube->NSWE];
		adress = (unsigned int *)cube->texture[cube->NSWE].adress;
	}
	else
	{
		texture = cube->texture[cube->frame];
		adress = (unsigned int *)cube->texture[cube->frame].adress;
	}
	i = 0;
	k = (int)(offset * texture.pix_w);
	l = top_pixel * texture.pix_h;
	scale = ((1 - 2 * top_pixel) / WIN_H) * texture.pix_h;
	while(i < WIN_H)
	{
		ft_putpixel(cube->ray.index, i, cube, adress[texture.pix_w  * (int)(l)  + k], 1);
		l += scale;
		i++;
	}
}

float added_angle(t_cube *cube)
{
	int	hor;
	int	ver;

	hor = 0;
	ver = 0;
	if (cube->input[KEY_W])
		ver++;
	if (cube->input[KEY_S])
		ver--;
	if (cube->input[KEY_A])
		hor--;
	if (cube->input[KEY_D])
		hor++;
	if (!hor && !ver)
		return (-1);
	if (hor && ver)
		return ((ver + 2) * hor * 0.25);
	return (hor * 0.5 + (ver + 1) / 2); 
}


void	move_player(t_cube *cube, float angle)
{
	int		map_grid_y;
	int		map_grid_x;
	float	new_x;
	float	new_y;

	angle = angle * PI;
	new_x = (cube->player.x + (cos(angle)/50));
	new_y = (cube->player.y - (sin(angle)/50	));
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
	if(cube->data.map[map_grid_y][(int)cube->player.x] == '1')
	{
		if(map_grid_y == cube->player.y)
			;
		else if(map_grid_y < cube->player.y)
			cube->player.y = map_grid_y + 1.01;
		else
			cube->player.y = map_grid_y - 0.01;
	}
	else
		cube->player.y = new_y;

	if(cube->data.map[(int)cube->player.y][map_grid_x] == '1')
	{
		if(map_grid_x == cube->player.x)
			;
		else if(map_grid_x < cube->player.x)
			cube->player.x = map_grid_x + 1.01;
		else
			cube->player.x = map_grid_x - 0.01;
	}
	else
		cube->player.x = new_x;
}

void moving (t_cube *cube)
{
	float angle;

	if (cube->input[KEY_LEFT])
		cube->player.angle += ROTATION_SPEED;
	if (cube->input[KEY_RIGHT])
		cube->player.angle -= ROTATION_SPEED;
	angle = added_angle(cube);
	if(angle != -1)
		move_player(cube, fix_angle(angle + cube->player.angle));	
}

void draw_wall_other(t_cube *cube, float pixel, float offset, int i)
{
	int		k;
	float	stat;
	float	l;
	unsigned int *adress;
	t_img_data texture;
	if(cube->NSWE != NORTH)
	{
		texture = cube->texture[cube->NSWE];
		adress = (unsigned int *)cube->texture[cube->NSWE].adress;
	}
	else
	{
		texture = cube->texture[cube->frame];
		adress = (unsigned int *)cube->texture[cube->frame].adress;
	}
	stat = texture.pix_h * pixel ;
	k = (int)floor(offset * texture.pix_w);
	l = 0;
	while(l < texture.pix_h)
	{
		ft_putpixel(cube->ray.index, i, cube, adress[texture.pix_w  * (int)floor(l) + k], 1);
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
		ft_putpixel(cube->ray.index, i, cube, cube->data.FC[0], 1);
		i++;
	}
	while(i < WIN_H - top)
	{
		ft_putpixel(cube->ray.index, i, cube, 16777215, 1);
		i++;
	}
	while(i < WIN_H)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->data.FC[1], 1);
		i++;
	}
}

void givemeplayer(t_cube *cube, int size_w, int size_h)
{
	int i = -4;
	int y;
	while(i != 4)
	{
		y = -4;
		while(y != 4)
		{
			display_pix(&cube->img, (cube->player.x * size_w) + i, (cube->player.y * size_h) + y, 0x0); 
			y++;
		}
		i++;
	}
		display_pix(&cube->img, (cube->player.x * size_w), (cube->player.y* size_h), 0x0); 
}

void wall_display(t_cube *cube, float dist, float offset)
{
	static float	tetta;
	float			wall_h;
	float			top_pixel;
	float			pixel;

	if(!tetta)
		tetta = tanf(FOV_H * PI / 360) * 2;
	wall_h = dist * tetta;
	pixel = wall_h / WIN_H;
	if(wall_h > 1)
	{
		wall_h = (wall_h - 1) / 2;
		top_pixel = wall_h / pixel;
		draw_other(top_pixel, cube);
		draw_wall_other(cube, pixel, offset, top_pixel);
	}
	else
	{

		top_pixel = WIN_H / (cube->texture[cube->NSWE].pix_h * wall_h);
		wall_h = (1 - wall_h) / 2;
		draw_wall(wall_h, cube, offset);
	}
	if(cube->ray.index < cube->minimap_w)
	{
		int size_w = cube->minimap_w / cube->data.map_w;
		int size_h = cube->minimap_h / cube->data.map_h;
		int i = 0;
		int pos_y = 0;
		int pos_x = cube->ray.index / size_w;

		while(i < cube->minimap_h)
		{
			if(cube->data.map[pos_y][pos_x] == '1')
				ft_putpixel(cube->ray.index, i, cube, 0x1e17fb, 0);
			else if(cube->data.map[pos_y][pos_x] == '0')
				ft_putpixel(cube->ray.index, i, cube, 0xffffff, 0);
			else
				ft_putpixel(cube->ray.index, i, cube, 0xffffff, 0);
			i++;
			if(i % size_h == 0 && pos_y < cube->data.map_h - 1)
				pos_y++;
		}
		givemeplayer(cube, size_w, size_h);
	}
}


void wall_check(float dist_x, float dist_y, t_cube *cube, float angle, float cosangled)
{
	float dist;
    float offset;

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
	if(cube->NSWE == WEST || cube->NSWE == NORTH)
		offset = 1 - offset;
	wall_display(cube, dist * cosangled, offset);
}

void raycasting(t_cube *cube)
{
    float fixed_angle[2];
    float angle;

	cube->ray.index = 0;
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