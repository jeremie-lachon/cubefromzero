/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:30:54 by dakojic           #+#    #+#             */
/*   Updated: 2024/12/25 21:39:52 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int player_filler(t_cube *cube)
{
	float fov_rad;

	if(cube->data.facing == 'N')
        cube->player.angle = PI / 2.0;
	if(cube->data.facing == 'S')
        cube->player.angle = (PI * 3) / 2;
	if(cube->data.facing == 'E')
        cube->player.angle = 0;
	if(cube->data.facing == 'W')
        cube->player.angle = PI;
	cube->player.fov_rad = (FOV * PI) / 180;
	fov_rad = cube->player.fov_rad;
	// cube->player.plane_x = cube->player.dir_x * tan(fov_rad / 2);
	// cube->player.plane_y = cube->player.dir_y * tan(fov_rad / 2);
	cube->player.x = cube->data.pos_x * CELL_SIZE + CELL_SIZE / 2;
	cube->player.y = cube->data.pos_y * CELL_SIZE + CELL_SIZE / 2;
	return (0);
}


void draw_pixel(t_img_data *img, int x, int y, int color)
{
    char *pixel;

    pixel = img->adress + (y * img->size + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

float angle_fix(float ray_angle)
{
    if(ray_angle < 0)
        ray_angle += (2 * PI);
    if(ray_angle > 2 * PI)
        ray_angle -= (2 * PI);
    return (ray_angle);

}

void display_pix(t_img_data *img, int x, int y, int color)
{
    char *dest;

    dest = img->adress + (y * img->size + x  * (img->bpp / 8));
    *(unsigned int *)dest = color;
}
void ft_putpixel(t_cube *cube, int ray, int i, int color)
{
    if(ray < 0 || ray >= WIN_W || i > WIN_H || i < 0)
        return ;
    display_pix(&cube->img, ray, i, color);
    
}
void draw_floor_ceiling(t_cube *cube, int ray, double top, double bot)
{
    int i;
    i = bot;

    while(i < WIN_H)
        ft_putpixel(cube, ray, i++, 0x00FF0060);
    i = 0;
    while(i < top)
        ft_putpixel(cube, ray, i++, 0x0000FF00);
}

t_img_data side_texture(t_cube *cube)
{
	cube->ray.ray_angle = angle_fix(cube->ray.ray_angle);
	if (cube->ray.flag == 0)
	{
		if (cube->ray.ray_angle > PI / 2 && cube->ray.ray_angle < 3 * (PI / 2))
			return (cube->texture[0]);
		else
			return (cube->texture[1]);
	}
	else
	{
		if (cube->ray.ray_angle > 0 && cube->ray.ray_angle < PI)
			return (cube->texture[2]);
		else
			return (cube->texture[3]);
	}
}
double get_offset_x(t_img_data *texture, t_cube *cube)
{
    double ret;

    if(cube->ray.flag == 1)
        ret = (int)fmodf((cube->ray.h_x * (texture->pix_w / CELL_SIZE)), texture->pix_w);
    else
        ret = (int)fmodf((cube->ray.v_y * (texture->pix_w / CELL_SIZE)), texture->pix_w);
    return (ret);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = c;
	return (b);
}


void draw_wall(t_cube *cube, double top, double bot, double wall)
{
    double off_x;
    double off_y;
    t_img_data text;
    unsigned int *arr;
    double fact;

    text = side_texture(cube);
    if(!text.adress)
        printf("Y A PLUS\n");
    arr = (unsigned int *)text.adress;
    fact = (double)text.pix_h / wall;
    off_x = get_offset_x(&text, cube);
    off_y = (top - (WIN_H / 2) + (wall / 2)) * fact;
    if(off_y < 0)
        off_y = 0;
    while(top < bot)
    {
        ft_putpixel(cube, cube->ray.index, top, reverse_bytes(arr[(int)off_y * text.pix_w + (int)off_x]));
        off_y += fact;
        top++;
    }
}
void    render_wall(t_cube *cube, int ray)
{
    double wall_h;
    double bot_pixel;
    double top_pixel;

    cube->ray.distance *= cos(angle_fix(cube->ray.ray_angle - cube->player.angle));
    wall_h = (CELL_SIZE / cube->ray.distance) * ((WIN_W / 2) / tan(cube->player.fov_rad / 2));
    bot_pixel = (WIN_H / 2) + (wall_h / 2);
    top_pixel = (WIN_H / 2) - (wall_h / 2);
    if(bot_pixel > WIN_H)
        bot_pixel = WIN_H;
    if(top_pixel < 0)
        top_pixel = 0;
    cube->ray.index = ray;
    draw_wall(cube, top_pixel, bot_pixel, wall_h);
    draw_floor_ceiling(cube, ray, top_pixel, bot_pixel);
}

int	inter_check(float angle, float *inter, float *step, int is_inter)
{
	if (is_inter)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += CELL_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += CELL_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

int	wall_hit(float x, float y, t_cube *cube)
{
	int	x_m;
	int	y_m;

	x_m = floor(x / CELL_SIZE);
	y_m = floor(y / CELL_SIZE);
	if (x_m < 0 || y_m < 0)
		return (0);
	if (y_m >= cube->data.map_h || x_m >= cube->data.map_w)
		return (0);
	if (cube->data.map[y_m] && x_m <= (int)strlen(cube->data.map[y_m]))
		if (cube->data.map[y_m][x_m] == '1'
			|| cube->data.map[y_m][x_m] == ' ')
			return (0);
	return (1);
}

float horizon_crossing(t_cube *cube, float angle)
{
    float hx;
    float hy;
    float steps_x;
    float steps_y;
    int pixel;

    steps_y = CELL_SIZE;
    steps_x = CELL_SIZE / tan(angle);
    hy = floor(cube->player.y / CELL_SIZE) * CELL_SIZE;
    pixel = inter_check(cube->player.angle, &hy, &steps_y, 1);
    hx = cube->player.x + (hy - cube->player.y) / tan(angle);
    if((unit_circle(angle, 'y') && steps_x > 0) || (!unit_circle(angle, 'y') && steps_x < 0))
        steps_x *= -1;
    while(wall_hit(hx, hy - pixel, cube))
    {
        hx += steps_x;
        hy += steps_y;
    }
    cube->ray.h_x = hx;
    cube->ray.h_y = hy;
    return (sqrt(pow(hx - cube->player.x, 2) + pow(hy - cube->player.y, 2)));
}

float vertical_crossing(t_cube *cube, float angle)
{
    float vx;
    float vy;
    float steps_x;
    float steps_y;
    int pixel;

    steps_x = CELL_SIZE;
    steps_y = CELL_SIZE / tan(angle);
    if (fabs(tan(angle)) < EPSILON)
        steps_y = LARGE_NUMBER;
    else
        steps_y = CELL_SIZE / tan(angle);
    vx = floor(cube->player.x / CELL_SIZE) * CELL_SIZE;
    pixel = inter_check(cube->player.angle, &vx, &steps_x, 0);
    vy = cube->player.y + (vx - cube->player.x) / tan(angle);
    if((unit_circle(angle, 'y') && steps_y > 0) || (!unit_circle(angle, 'y') && steps_y < 0))
        steps_y *= -1;
    while(wall_hit(vy, vx - pixel, cube))
    {
        vx += steps_x;
        vy += steps_y;
    }
    cube->ray.v_x = vx;
    cube->ray.v_y = vy;
    return (sqrt(pow(vx - cube->player.x, 2) + pow(vy - cube->player.y, 2)));
}
void render(t_cube *cube)
{
    double h_crossing;
    double v_crossing;
    int ray;

    ray = 0;
    cube->ray.ray_angle = cube->player.angle - (cube->player.fov_rad / 2);
    while(ray < WIN_W)
    {
        cube->ray.flag = 0;
        h_crossing = horizon_crossing(cube, angle_fix(cube->ray.ray_angle));
        v_crossing = vertical_crossing(cube, angle_fix(cube->ray.ray_angle));
        if(v_crossing <= h_crossing)
            cube->ray.distance = v_crossing;
        else
        {
            cube->ray.distance = h_crossing;
            cube->ray.flag = 1;
        }
        render_wall(cube, ray);
        ray++;
        cube->ray.ray_angle += (cube->player.fov_rad / WIN_W);
        cube->ray.ray_angle = angle_fix(cube->ray.ray_angle);
    }
}
void rotate_player(t_cube *cube, int key)
{
    cube->player.angle += ROTATION_SPEED * key;
    cube->player.angle = angle_fix(cube->player.angle);
}
void	move_player(t_cube *cube, double angle)
{
	int		map_grid_y;
	int		map_grid_x;
	double	new_x;
	double	new_y;

	new_x = (cube->player.x + cos(angle));
	new_y = (cube->player.y + sin(angle));
	map_grid_x = ((int)new_x / CELL_SIZE);
	map_grid_y = ((int)new_y / CELL_SIZE);
	if (cube->data.map[map_grid_y][map_grid_x] != '1'
		&& (cube->data.map[map_grid_y][(int)cube->player.x
			/ CELL_SIZE] != '1' || cube->data.map[(int)cube->player.y
			/ CELL_SIZE][map_grid_x] != '1'))
	{
		cube->player.x = new_x;
		cube->player.y = new_y;
        printf("La position est %f et %f\n", cube->player.x, cube->player.y);
	}
}
void moving(t_cube *cube)
{
    rotate_player(cube, cube->inputs[126] - cube->inputs[127]);
    if(cube->inputs[119]) //w
        move_player(cube, angle_fix(cube->player.angle));
    if(cube->inputs[115]) //s
        move_player(cube, angle_fix(cube->player.angle + PI));
    if(cube->inputs[97]) //d
        move_player(cube, angle_fix(cube->player.angle - (PI / 2.0)));
    if(cube->inputs[100]) //a
        move_player(cube, angle_fix(cube->player.angle + (PI / 2.0)));
}
int loop_render(t_cube *cube)
{
	render(cube);
    mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img_ptr, 0, 0);
	moving(cube);
    return (0);
}

int key_release(int keysym, t_cube* cube)
{
	if (keysym >= 32 && keysym < 126)
		cube->inputs[keysym] = 0;
	if (keysym == XK_Right)
		cube->inputs[126] = 0;
	if (keysym == XK_Left)
		cube->inputs[127] = 0;
	return (0);
}

int game(t_cube *cube)
{
	init_mlx(cube);

	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, &key_press, cube);
    mlx_hook(cube->win_ptr, KeyRelease, KeyReleaseMask, &key_release, cube);
	// mlx_hook(cube->win_ptr, 17, 0, &escape, cube);
	mlx_loop_hook(cube->mlx_ptr, &loop_render, cube);
	mlx_loop(cube->mlx_ptr);
	return (0);
}
int main(void)
{
    t_cube cube;

    cube = (t_cube){0};
   	map_filler(&cube.data);
	player_filler(&cube);
	game(&cube);
    return (0);
}