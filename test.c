/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:30:54 by dakojic           #+#    #+#             */
/*   Updated: 2024/12/24 18:22:04 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_filler(t_data *data)
{
    data->map = calloc(10, sizeof(char *));
    if (!data->map)
        return (-1);

    data->map_h = 9;
    data->map_w = 25;
    data->map[0] = strdup("1111111111111111111111111");
    data->map[1] = strdup("1000000000000000000100001");
    data->map[2] = strdup("1001000000000P00000000001");
    data->map[3] = strdup("1001000000000000001000001");
    data->map[4] = strdup("1001000000000000001000001");
    data->map[5] = strdup("1001000000100000001000001");
    data->map[6] = strdup("1001000000000000001000001");
    data->map[7] = strdup("1001000000001000001000001");
    data->map[8] = strdup("1111111111111111111111111");
    data->map[9] = NULL;

    data->pos_x = 5;
    data->pos_y = 5;
	data->facing = 'N';
    return (0);
}



void direction_filler(t_player *player, int x, int y)
{
	player->dir_x = x;
	player->dir_y = y;
}

int player_filler(t_cube *cube)
{
	float fov_rad;

	if(cube->data.facing == 'N')
		direction_filler(&cube->player, 0, 1);
	if(cube->data.facing == 'S')
		direction_filler(&cube->player, 0, -1);
	if(cube->data.facing == 'W')
		direction_filler(&cube->player, -1, 0);
	if(cube->data.facing == 'E')
		direction_filler(&cube->player, 1, 0);
	cube->player.fov_rad = FOV * PI / 180;
	fov_rad = cube->player.fov_rad;
	cube->player.plane_x = cube->player.dir_x * tan(fov_rad / 2);
	cube->player.plane_y = cube->player.dir_y * tan(fov_rad / 2);
	cube->player.x = cube->data.pos_x * CELL_SIZE;
	cube->player.y = cube->data.pos_y * CELL_SIZE;
	return (0);
}
int init_mlx(t_cube *cube)
{
	cube->mlx_ptr = mlx_init();

	cube->img.img_ptr = mlx_new_image(cube->mlx_ptr, WIN_W, WIN_H);
	// protection
	cube->img.adress = mlx_get_data_addr((cube)->img.img_ptr, 
												&cube->img.bpp, 
												&cube->img.size, 
												&cube->img.endl);
	// protection
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIN_W, WIN_H, "Cub3d");
	// protection
	return (0);
}

int	escape(t_cube *cube)
{
	int i;
	i = -1;
		//cube->win_ptr vide ????
	mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	mlx_destroy_image(cube->mlx_ptr, cube->img.img_ptr);
	mlx_destroy_display(cube->mlx_ptr);
	free(cube->mlx_ptr);
	
	while(cube->data.map[++i])
		free(cube->data.map[i]);
	free(cube->data.map);
	exit(0);
}

int key_press(int keysym, t_cube *cube)
{
	if (keysym == XK_Escape)
		escape(cube);
	else if (keysym == XK_w)
		printf("Go go go\n");
	else if (keysym == XK_s)
		printf("Backped\n");
	else if (keysym == XK_a)
		printf("Straf left\n");
	else if (keysym == XK_d)
		printf("Straf droite\n");
	else if (keysym == XK_Left )
		printf("On tourne a gauche\n");
	else if (keysym == XK_Right)
		printf("On tourne a droite\n");
	return (0);
}

int game(t_cube *cube)
{
	init_mlx(cube);

	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, &key_press, cube);
	mlx_hook(cube->win_ptr, 17, 0, &escape, cube);

	if(cube->mlx_ptr)
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