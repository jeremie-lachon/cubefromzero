/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:30:54 by dakojic           #+#    #+#             */
/*   Updated: 2024/12/24 20:16:44 by dakojic          ###   ########.fr       */
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
	// cube->player.plane_x = cube->player.dir_x * tan(fov_rad / 2);
	// cube->player.plane_y = cube->player.dir_y * tan(fov_rad / 2);
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

void draw_pixel(t_img_data *img, int x, int y, int color)
{
    char *pixel;

    pixel = img->adress + (y * img->size + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

void render_floor_and_ceiling(t_cube *cube)
{
    int x, y;

    // Couleur du ciel (par exemple, bleu clair)
    int sky_color = 0x67CEEB;
    // Couleur du sol (par exemple, vert foncé)
    int floor_color = 0x928B22;

    // Remplir la moitié supérieure de l'écran avec la couleur du ciel
    for (y = 0; y < WIN_H / 2; y++)
    {
        for (x = 0; x < WIN_W; x++)
        {
            draw_pixel(&cube->img, x, y, sky_color);
        }
    }

    // Remplir la moitié inférieure de l'écran avec la couleur du sol
    for (y = WIN_H / 2; y < WIN_H; y++)
    {
        for (x = 0; x < WIN_W; x++)
        {
            draw_pixel(&cube->img, x, y, floor_color);
        }
    }
}

float horizontal_intersection(t_cube *cube, float ray_angle)
{
    float x_intercept, y_intercept;
    float x_step, y_step;
    int map_x, map_y;
    float distance = 0.0;

    // Calculer les coordonnées de l'intersection initiale
    y_intercept = floor(cube->player.y / CELL_SIZE) * CELL_SIZE;
    if (ray_angle > 0 && ray_angle < PI)
        y_intercept += CELL_SIZE;
    else
        y_intercept -= 0.0001;

    x_intercept = cube->player.x + (y_intercept - cube->player.y) / tan(ray_angle);

    // Calculer les pas pour les intersections suivantes
    y_step = CELL_SIZE;
    if (!(ray_angle > 0 && ray_angle < PI))
        y_step *= -1;

    x_step = CELL_SIZE / tan(ray_angle);
    if ((ray_angle > PI / 2 && ray_angle < 3 * PI / 2) && x_step > 0)
        x_step *= -1;
    if (!(ray_angle > PI / 2 && ray_angle < 3 * PI / 2) && x_step < 0)
        x_step *= -1;

    // Vérifier les intersections successives
    while (1)
    {
        map_x = (int)(x_intercept / CELL_SIZE);
        map_y = (int)(y_intercept / CELL_SIZE);

        // Vérifier si l'intersection est dans les limites de la carte
        if (map_x >= 0 && map_x < cube->data.map_w && map_y >= 0 && map_y < cube->data.map_h)
        {
            // Vérifier si l'intersection est avec un mur
            if (cube->data.map[map_y][map_x] == '1')
            {
                distance = sqrt((x_intercept - cube->player.x) * (x_intercept - cube->player.x) +
                                (y_intercept - cube->player.y) * (y_intercept - cube->player.y));
                break;
            }
        }
        else
        {
            // Si l'intersection est hors des limites de la carte, arrêter la recherche
            distance = FLT_MAX;
            break;
        }

        // Passer à l'intersection suivante
        x_intercept += x_step;
        y_intercept += y_step;
    }

    return distance;
}
float vertical_intersection(t_cube *cube, float ray_angle)
{
    float x_intercept, y_intercept;
    float x_step, y_step;
    int map_x, map_y;
    float distance = 0.0;

    // Calculer les coordonnées de l'intersection initiale
    x_intercept = floor(cube->player.x / CELL_SIZE) * CELL_SIZE;
    if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2)
        x_intercept += CELL_SIZE;
    else
        x_intercept -= 0.0001;

    y_intercept = cube->player.y + (x_intercept - cube->player.x) * tan(ray_angle);

    // Calculer les pas pour les intersections suivantes
    x_step = CELL_SIZE;
    if (!(ray_angle < PI / 2 || ray_angle > 3 * PI / 2))
        x_step *= -1;

    y_step = CELL_SIZE * tan(ray_angle);
    if ((ray_angle > 0 && ray_angle < PI) && y_step < 0)
        y_step *= -1;
    if (!(ray_angle > 0 && ray_angle < PI) && y_step > 0)
        y_step *= -1;

    // Vérifier les intersections successives
    while (1)
    {
        map_x = (int)(x_intercept / CELL_SIZE);
        map_y = (int)(y_intercept / CELL_SIZE);

        // Vérifier si l'intersection est dans les limites de la carte
        if (map_x >= 0 && map_x < cube->data.map_w && map_y >= 0 && map_y < cube->data.map_h)
        {
            // Vérifier si l'intersection est avec un mur
            if (cube->data.map[map_y][map_x] == '1')
            {
                distance = sqrt((x_intercept - cube->player.x) * (x_intercept - cube->player.x) +
                                (y_intercept - cube->player.y) * (y_intercept - cube->player.y));
                break;
            }
        }
        else
        {
            // Si l'intersection est hors des limites de la carte, arrêter la recherche
            distance = FLT_MAX;
            break;
        }

        // Passer à l'intersection suivante
        x_intercept += x_step;
        y_intercept += y_step;
    }

    return distance;
}
// void render_floor_and_ceiling(t_cube *cube)
// {
//     int x, y;

//     // Couleur du ciel (par exemple, bleu clair)
//     int sky_color = 0x87CEEB;
//     // Couleur du sol (par exemple, vert foncé)
//     int floor_color = 0x228B22;

//     // Remplir la moitié supérieure de l'écran avec la couleur du ciel
//     for (y = 0; y < WIN_H / 2; y++)
//     {
//         for (x = 0; x < WIN_W; x++)
//         {
//             draw_pixel(&cube->img, x, y, sky_color);
//         }
//     }

//     // Remplir la moitié inférieure de l'écran avec la couleur du sol
//     for (y = WIN_H / 2; y < WIN_H; y++)
//     {
//         for (x = 0; x < WIN_W; x++)
//         {
//             draw_pixel(&cube->img, x, y, floor_color);
//         }
//     }
// }

void cast(t_cube *cube)
{
    int ray;
    float vertic_inter, horiz_inter;

    render_floor_and_ceiling(cube); // Ajoutez cette ligne pour rendre le sol et le ciel

    ray = 0;
    cube->ray.ray_angle = cube->player.angle - (cube->player.fov_rad / 2);
    while (ray < WIN_W)
    {
        vertic_inter = vertical_intersection(cube, cube->ray.ray_angle);
        horiz_inter = horizontal_intersection(cube, cube->ray.ray_angle);
        if (vertic_inter <= horiz_inter)
        {
            cube->ray.distance = vertic_inter;
            cube->ray.flag = 0; // Intersection verticale
        }
        else
        {
            cube->ray.distance = horiz_inter;
            cube->ray.flag = 1; // Intersection horizontale
        }

        ray++;
        cube->ray.ray_angle += (cube->player.fov_rad / WIN_W);
    }
}

int loop_render(t_cube *cube)
{
	cast(cube);
	return (0);
}


int game(t_cube *cube)
{
	init_mlx(cube);

	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, &key_press, cube);
	mlx_hook(cube->win_ptr, 17, 0, &escape, cube);
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