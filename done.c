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
    data->map[3] = strdup("100000000000000000000001");
    data->map[2] = strdup("100000000000000000000001");
    data->map[1] = strdup("100000000111111000000001");
	data->map[0] = strdup("111111111111111111111111");
    data->pos_x = 1;
    data->pos_y = 4;
	data->facing = 'N';
    return (0);
}

// int	escape(t_cube *cube)
// {
// 	int i;
// 	i = -1;
// 		//cube->win_ptr vide ????
// 	mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
// 	mlx_destroy_image(cube->mlx_ptr, cube->img.img_ptr);
// 	mlx_destroy_display(cube->mlx_ptr);
// 	free(cube->mlx_ptr);
	
// 	while(cube->data.map[++i])
// 		free(cube->data.map[i]);
// 	free(cube->data.map);
// 	exit(0);
// }

// int key_press(int keysym, t_cube *cube)
// {
// 	printf("Im getting %d\n", keysym);
// 	if (keysym == XK_Escape)
// 		escape(cube);
// 	if (keysym >= 32 && keysym < 126)
// 		cube->inputs[keysym] = 1;
// 	if (keysym == XK_Right)
// 		cube->inputs[126] = 1;
// 	if (keysym == XK_Left)
// 		cube->inputs[127] = 1;
// 	return (0);
// }

// int init_mlx(t_cube *cube)
// {
// 	cube->mlx_ptr = mlx_init();

// 	cube->img.img_ptr = mlx_new_image(cube->mlx_ptr, WIN_W, WIN_H);
// 	// protection
// 	cube->img.adress = mlx_get_data_addr((cube)->img.img_ptr, 
// 												&cube->img.bpp, 
// 												&cube->img.size, 
// 												&cube->img.endl);
// 	// protection
//     cube->texture[0].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "/mnt/nfs/homes/dakojic/NEW_CUBE/texture/west.xpm", &cube->texture[0].pix_w, &cube->texture[0].pix_h);  //west
//     cube->texture[1].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "/mnt/nfs/homes/dakojic/NEW_CUBE/texture/east.xpm", &cube->texture[1].pix_w, &cube->texture[1].pix_h);   //east                          
//     cube->texture[2].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "/mnt/nfs/homes/dakojic/NEW_CUBE/texture/1000x1600.xpm", &cube->texture[2].pix_w, &cube->texture[2].pix_h);   // nord                          
//     cube->texture[3].img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, "/mnt/nfs/homes/dakojic/NEW_CUBE/texture/1000_1600.xpm", &cube->texture[3].pix_w, &cube->texture[3].pix_h);          // sud


//     cube->texture[0].adress = mlx_get_data_addr(cube->texture[0].img_ptr, &cube->texture[0].bpp, &cube->texture[0].size, &cube->texture[0].endl);
//     cube->texture[1].adress = mlx_get_data_addr(cube->texture[1].img_ptr, &cube->texture[1].bpp, &cube->texture[1].size, &cube->texture[1].endl);
//     cube->texture[2].adress = mlx_get_data_addr(cube->texture[2].img_ptr, &cube->texture[2].bpp, &cube->texture[2].size, &cube->texture[2].endl);
//     cube->texture[3].adress = mlx_get_data_addr(cube->texture[3].img_ptr, &cube->texture[3].bpp, &cube->texture[3].size, &cube->texture[3].endl);
//     cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIN_W, WIN_H, "Cub3d");
// 	// protection
// 	return (0);
// }