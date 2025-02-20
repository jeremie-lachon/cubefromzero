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


// void mouse_rotation(t_cube *cube)
// {
//     mlx_mouse_get_pos(cube->mlx_ptr, cube->win_ptr, &cube->mouse_x, &cube->mouse_y);
//     if(cube->mouse_x < 0 || cube->mouse_x > WIN_W || cube->mouse_y < 0 || cube->mouse_y > WIN_H)
//         cube->mouse_x = HALF_WIDTH;
//     if(cube->mouse_x > HALF_WIDTH + 150)
//         cube->input[MOUSE_LEFT] = 1;
//     else
//         cube->input[MOUSE_LEFT] = 0;
//     if(cube->mouse_x < HALF_WIDTH - 150)
//         cube->input[MOUSE_RIGHT] = 1;
//     else
//         cube->input[MOUSE_RIGHT] = 0;
// }

// int game(t_cube *cube)
// {
// 	init_mlx(cube);
// 	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, &key_press, cube);
//     mlx_hook(cube->win_ptr, KeyRelease, KeyReleaseMask, &key_release, cube);
// 	mlx_hook(cube->win_ptr, 17, 0, &escape, cube);
// 	mlx_loop_hook(cube->mlx_ptr, &loop_render, cube);

// 	mlx_loop(cube->mlx_ptr);
// 	return (0);
// }
// int main(void)
// {
//     t_cube *cube;

//     cube = calloc(1 , sizeof(t_cube));
//     // cube = (t_cube){0};
//    	map_filler(&cube->data);
// 	player_filler(cube);
// 	game(cube);
//     return (0);
// }

int basic_checks(int ac, char **av, int *fd)
{
	if (ac != 2)
		return (write(1, "Error\nWrong number of arguments.\n", 33), 1);
	if (cub_check(av[1]))
		return (write(1, "Error\nMap is not using .cub extension.\n", 39), 1);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (perror("Error\n"), 1);
    return (0);
}

int init(t_parse **parse, int fd, t_mlx **mlx, t_cube **cube)
{
    *parse = parseinit();
	if (!*parse || parse_filler(fd, *parse))
		return (perror("Error\n"), parsefree(*parse), 1);
	*mlx = 0;
	if (ft_mlx_start(mlx))
		return (perror("Error\n"), free(*mlx), parsefree(*parse), 1);
	*cube = parse_to_cube(*parse, *mlx);
    if (!*cube)
        return (1);
    return (0);
}
int minimap_sizing(t_cube *cube)
{
    if (cube->data.map_h > 300 || cube->data.map_w > 300)
    {
        return (perror("Error : Map size is over 300!"), free_cube(cube), 1);
    }
    if (WIN_H < 300 || WIN_W < 300)
    {
        return (perror("Error : Window size is undersized."), free_cube(cube), 1);
    }
	cube->minimap_w = 300;
	cube->minimap_h = 300;
    return (0);
}
int main(int ac, char **av)
{
	t_parse *parse;
	t_cube  *cube;  
	t_mlx   *mlx;
	int     fd;
    if (basic_checks(ac, av, &fd) || init(&parse, fd, &mlx, &cube) || minimap_sizing(cube))
    {
        return (1);
    }
	mlx_hook(cube->mlx->win, KeyPress, KeyPressMask, &key_press, cube);
	mlx_hook(cube->mlx->win, KeyRelease, KeyReleaseMask, &key_release, cube);
	mlx_hook(cube->mlx->win, 17, 0, &escape, cube);
	mlx_loop_hook(cube->mlx->mlx, &loop_render, cube);
	mlx_loop(cube->mlx->mlx);
	free_cube(cube);
	return (0);
}