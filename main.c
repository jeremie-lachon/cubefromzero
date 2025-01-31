/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:30:54 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/16 16:57:47 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int player_filler(t_cube *cube)
{

	if(cube->data.facing == 'N')
        cube->player.angle = 0.50F;
	if(cube->data.facing == 'S')
        cube->player.angle = 1.50F;
	if(cube->data.facing == 'E')
        cube->player.angle = 1.0F;
	if(cube->data.facing == 'W')
        cube->player.angle = 0.0F;
	cube->player.x = cube->data.pos_x + 0.5F;
	cube->player.y = cube->data.pos_y + 0.5F;
	return (0);
}

void mouse_rotation(t_cube *cube)
{
    mlx_mouse_get_pos(cube->mlx_ptr, cube->win_ptr, &cube->mouse_x, &cube->mouse_y);
    if(cube->mouse_x < 0 || cube->mouse_x > WIN_W || cube->mouse_y < 0 || cube->mouse_y > WIN_H)
        cube->mouse_x = HALF_WIDTH;
    if(cube->mouse_x > HALF_WIDTH + 150)
        cube->input[MOUSE_LEFT] = 1;
    else
        cube->input[MOUSE_LEFT] = 0;
    if(cube->mouse_x < HALF_WIDTH - 150)
        cube->input[MOUSE_RIGHT] = 1;
    else
        cube->input[MOUSE_RIGHT] = 0;
}

void ft_putmap(int ray, int i, t_cube *cube, int color)
{
	if (ray < 0 || ray >= cube->minimap_w || i > cube->minimap_h || i < 0)
		return ;
    display_pix(&cube->minimap, ray, i, color);
}

void draw_map_line(t_cube *cube, int x)
{
    int y;

    y = 0;
    while(y < cube->minimap_h)
    {   
        ft_putpixel(x, y, cube, 0xea0000, 0);
        y++;
    }
}
void draw_minimap(t_cube *cube)
{
    int i;

    i = 0;
    while(i < cube->minimap_w)
    {
        draw_map_line(cube, i);
        i++;
    }
}

int loop_render(t_cube *cube)
{
	static	int	i;

	if (!i)
	{
		cube->img = cube->image1;
		i++;
	}
	else
	{
		cube->img = cube->image2;
		i--;
	}
	gettimeofday(&cube->time, NULL);
	cube->frame = cube->time.tv_sec % 4;
	raycasting(cube);
    mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img.img_ptr, 0, 0);
    moving(cube);
    mouse_rotation(cube);
    return (0);
}

int game(t_cube *cube)
{
	init_mlx(cube);
	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, &key_press, cube);
    mlx_hook(cube->win_ptr, KeyRelease, KeyReleaseMask, &key_release, cube);
	mlx_hook(cube->win_ptr, 17, 0, &escape, cube);
	mlx_loop_hook(cube->mlx_ptr, &loop_render, cube);

	mlx_loop(cube->mlx_ptr);
	return (0);
}
int main(void)
{
    t_cube *cube;

    cube = calloc(1 , sizeof(t_cube));
    // cube = (t_cube){0};
   	map_filler(&cube->data);
	player_filler(cube);
	game(cube);
    return (0);
}