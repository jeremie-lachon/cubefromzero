#include "cub3d.h"

int map_filler(t_data *data)
{
    data->map = calloc(11, sizeof(char *));
    if (!data->map)
        return (-1);

    data->map_h = 11;
    data->map_w = 54;
  	
	data->map[10] = strdup("     1111111111111111111111111111111111111111111111111111111111");
    data->map[9] = strdup("1111111000000000000000001111111111111111111111111111111111111111");
    data->map[8] = strdup("111111111111110000000001111111111111111111111111111111111111111");
    data->map[7] = strdup("111111111111110000000001111111111111111111111111111111111111111");
    data->map[6] = strdup("100000000000000000000001111111111111111111111111111111111111111");
    data->map[5] = strdup("111000000000000000000000000000000000000000000000000111111111111");
    data->map[4] = strdup("100000000000000000000001111111111111111111111111111111111111111");
    data->map[3] = strdup("111111111111110000000001111111111111111111111111111111111111111");
    data->map[2] = strdup("111111111111110000000001111111111111111111111111111111111111111");
    data->map[1] = strdup("100000000000000000000001111111111111111111111111111111111111111");
	data->map[0] = strdup("111111111111111111111111111111111111111111111111111111111111111");
    data->pos_x = 22;
    data->pos_y = 4;
	data->facing = 'E';
	data->FC[0] = 0x00FF3330;
	data->FC[1] = 0x00ffadae;
    return (0);
}

int	escape(t_cube *cube)
{
	printf("CUIS LA\n");
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

	// cube->input[0] W
	// cube->input[1] S
	// cube->input[2] A
	// cube->input[3] D
	// cube->input[4] LEFT
	// cube->input[5] RIGHT
	if (keysym == XK_Escape)
		escape(cube);
	if(keysym == XK_w)
	{	
		cube->input[KEY_W] = 1;
	}
	if(keysym == XK_s)
		cube->input[KEY_S] = 1;
	if(keysym == XK_d)
		cube->input[KEY_A] = 1;
	if(keysym == XK_a)
		cube->input[KEY_D] = 1;
	if (keysym == XK_Right)
		cube->input[KEY_LEFT] = 1;
	if (keysym == XK_Left)
		cube->input[KEY_RIGHT] = 1;

	// if(cube->player.angle > 2 || cube->player.angle < 0)
	// 	cube->player.angle = fix_angle(cube->player.angle);
	return (0);
}

int key_release(int keysym, t_cube *cube)
{

	if(keysym == 3)
		cube->input[MOUSE_LEFT] = 0;
	if(keysym == XK_w)
		cube->input[KEY_W] = 0;
	if(keysym == XK_s)
		cube->input[KEY_S] = 0;
	if(keysym == XK_d)
		cube->input[KEY_A] = 0;
	if(keysym == XK_a)
		cube->input[KEY_D] = 0;
	if (keysym == XK_Right)
		cube->input[KEY_LEFT] = 0;
	if (keysym == XK_Left)
		cube->input[KEY_RIGHT] = 0;
	return (0);
}

int init_mlx(t_cube *cube)
{
	cube->mlx_ptr = mlx_init();
	if(!cube->mlx_ptr)
	{
		printf("bug cube->mlx_ptr\n");
		exit(4);
	}
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
	cube->minimap.img_ptr = mlx_new_image(cube->mlx_ptr, cube->minimap_w, cube->minimap_h);
	if(!cube->minimap.img_ptr)
	{
		printf("cube->minimap.img_ptr failed\n");
		exit(1);
	}
	// protection
	cube->minimap.adress = mlx_get_data_addr((cube)->minimap.img_ptr, 
												&cube->minimap.bpp, 
												&cube->minimap.size, 
												&cube->minimap.endl);

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
	cube->texture[FROID1].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/froid_1.xpm", &cube->texture[FROID1].pix_w, &cube->texture[FROID1].pix_h);
    if(!cube->texture[FROID1].img_ptr)
	{
		printf("cube->texture[FROID1].img_ptr bug\n");
		exit(1);
	}
		cube->texture[FROID2].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/froid_2.xpm", &cube->texture[FROID2].pix_w, &cube->texture[FROID2].pix_h);
    if(!cube->texture[FROID2].img_ptr)
	{
		printf("cube->texture[FROID2].img_ptr bug\n");
		exit(1);
	}

	cube->texture[FROID3].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/froid_3.xpm", &cube->texture[FROID3].pix_w, &cube->texture[FROID3].pix_h);
    if(!cube->texture[FROID3].img_ptr)
	{
		printf("cube->texture[FROID3].img_ptr bug\n");
		exit(1);
	}

	cube->texture[FROID4].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "./texture/froid_4.xpm", &cube->texture[FROID4].pix_w, &cube->texture[FROID4].pix_h);
    if(!cube->texture[FROID4].img_ptr)
	{
		printf("cube->texture[FROID4].img_ptr bug\n");
		exit(1);
	}

    cube->texture[FROID1].adress = mlx_get_data_addr(cube->texture[FROID1].img_ptr, &cube->texture[FROID1].bpp, &cube->texture[FROID1].size, &cube->texture[FROID1].endl);
    cube->texture[FROID2].adress = mlx_get_data_addr(cube->texture[FROID2].img_ptr, &cube->texture[FROID2].bpp, &cube->texture[FROID2].size, &cube->texture[FROID2].endl);
    cube->texture[FROID3].adress = mlx_get_data_addr(cube->texture[FROID3].img_ptr, &cube->texture[FROID3].bpp, &cube->texture[FROID3].size, &cube->texture[FROID3].endl);
    cube->texture[FROID4].adress = mlx_get_data_addr(cube->texture[FROID4].img_ptr, &cube->texture[FROID4].bpp, &cube->texture[FROID4].size, &cube->texture[FROID4].endl);

    cube->texture[EAST].adress = mlx_get_data_addr(cube->texture[EAST].img_ptr, &cube->texture[EAST].bpp, &cube->texture[EAST].size, &cube->texture[EAST].endl);
    cube->texture[WEST].adress = mlx_get_data_addr(cube->texture[WEST].img_ptr, &cube->texture[WEST].bpp, &cube->texture[WEST].size, &cube->texture[WEST].endl);
    cube->texture[NORTH].adress = mlx_get_data_addr(cube->texture[NORTH].img_ptr, &cube->texture[NORTH].bpp, &cube->texture[NORTH].size, &cube->texture[NORTH].endl);
    cube->texture[SOUTH].adress = mlx_get_data_addr(cube->texture[SOUTH].img_ptr, &cube->texture[SOUTH].bpp, &cube->texture[SOUTH].size, &cube->texture[SOUTH].endl);
    cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIN_W, WIN_H, "Cub3d");
	int h, w;
	if(cube->data.map_w > cube->data.map_h)
	{
		h = 20;
		w = 10;
	}	
	else if(cube->data.map_w < cube->data.map_h)
	{
		w = 20;
		h = 10;
	}	
	else
	{
		w = 20;
		h = 10;
	}
	cube->minimap_w = (cube->data.map_w) * w;
	cube->minimap_h = cube->data.map_h * h;
	// protection
	return (0);
}