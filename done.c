#include "cub3d.h"

int map_filler(t_data *data)
{
    data->map = calloc(6, sizeof(char *));
    if (!data->map)
        return (-1);

    data->map_h = 6;
    data->map_w = 25;
  	
    data->map[5] = strdup("111111111111111111111111");
    data->map[4] = strdup("100000000000000000000001");
    data->map[3] = strdup("111111111111110000000001");
    data->map[2] = strdup("111111111111110000000001");
    data->map[1] = strdup("100000000000000000000001");
	data->map[0] = strdup("111111111111111111111111");
    data->pos_x = 22;
    data->pos_y = 4;
	data->facing = 'E';
	data->FC[0] = 0x00FF3330;
	data->FC[1] = 0x00ffadae;
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
	float angle;
	int check;

	angle = cube->player.angle;
	check = 0;
	if (keysym == XK_Escape)
		escape(cube);
	if(keysym == XK_w)
	{
		angle += 1;
		check = 1;
	}	if(keysym == XK_s)
	{
		check = 1;
	}
	if(keysym == XK_d)
	{
		angle -= 0.5;
		check = 1;
	}
	if(keysym == XK_a)
	{	angle += 0.5;	
			check = 1;
	}
	// if(keysym == XK_s)
	// 	move_player(cube, cube->player.angle);
	// if(keysym == XK_w)
	// 	move_player(cube, cube->player.angle + 1);
	// if(keysym == XK_a)
	// 	move_player(cube, cube->player.angle - 0.5);
	// if(keysym == XK_d)
	// 	move_player(cube, cube->player.angle + 0.5);
	if (keysym == XK_Right)
		cube->player.angle += ROTATION_SPEED;
	if (keysym == XK_Left)
		cube->player.angle -= ROTATION_SPEED;
	if(cube->player.angle > 2 || cube->player.angle < 0)
		cube->player.angle = fix_angle(cube->player.angle);
	if(check)move_player(cube, angle);
	return (0);
}

int init_mlx(t_cube *cube)
{
	cube->mlx_ptr = mlx_init();

	cube->image1.img_ptr = mlx_new_image(cube->mlx_ptr, WIN_W, WIN_H);
	// protection
	cube->image1.adress = mlx_get_data_addr((cube)->image1.img_ptr, 
												&cube->image1.bpp, 
												&cube->image1.size, 
												&cube->image1.endl);
	// protection
	cube->image2.img_ptr = mlx_new_image(cube->mlx_ptr, WIN_W, WIN_H);
	// protection
	cube->image2.adress = mlx_get_data_addr((cube)->image2.img_ptr, 
												&cube->image2.bpp, 
												&cube->image2.size, 
												&cube->image2.endl);
	// protection
    cube->texture[EAST].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/e.xpm", &cube->texture[EAST].pix_w, &cube->texture[EAST].pix_h);  //west
    if(!cube->texture[EAST].img_ptr)
	{
		printf("cube->texture[EAST].img_ptr bug\n");
		exit(1);
	}
	cube->texture[SOUTH].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/s.xpm", &cube->texture[SOUTH].pix_w, &cube->texture[SOUTH].pix_h);   //east                          
    if(!cube->texture[SOUTH].img_ptr)
	{
		printf("cube->texture[SOUTH].img_ptr bug\n");
		exit(1);
	}
	cube->texture[NORTH].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/n.xpm", &cube->texture[NORTH].pix_w, &cube->texture[NORTH].pix_h);   // nord                          
    if(!cube->texture[NORTH].img_ptr)
	{
		printf("cube->texture[2].img_ptr bug\n");
		exit(1);
	}
	cube->texture[WEST].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/w.xpm", &cube->texture[WEST].pix_w, &cube->texture[WEST].pix_h);          // sud
    if(!cube->texture[WEST].img_ptr)
	{
		printf("cube->texture[WEST].img_ptr bug\n");
		exit(1);
	}

    cube->texture[EAST].adress = mlx_get_data_addr(cube->texture[EAST].img_ptr, &cube->texture[EAST].bpp, &cube->texture[EAST].size, &cube->texture[EAST].endl);
    cube->texture[WEST].adress = mlx_get_data_addr(cube->texture[WEST].img_ptr, &cube->texture[WEST].bpp, &cube->texture[WEST].size, &cube->texture[WEST].endl);
    cube->texture[NORTH].adress = mlx_get_data_addr(cube->texture[NORTH].img_ptr, &cube->texture[NORTH].bpp, &cube->texture[NORTH].size, &cube->texture[NORTH].endl);
    cube->texture[SOUTH].adress = mlx_get_data_addr(cube->texture[SOUTH].img_ptr, &cube->texture[SOUTH].bpp, &cube->texture[SOUTH].size, &cube->texture[SOUTH].endl);
    cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIN_W, WIN_H, "Cub3d");

	// protection
	return (0);
}