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

static int cub_check(char *str)
{
	int i;

	i = strlen(str);
	if (i < 5)
		return (1);
	i--;
	if (str[i] != 'b')
		return (1);
	if (str[i - 1] != 'u')
		return (1);
	if (str[i - 2] != 'c')
		return (1);
	if (str[i - 3] != '.')
		return (1);
	return (0);
}

static int	basic_checks(int ac, char **av, int *fd)
{
	if (ac != 2)
		return (write(1, "Error\nWrong number of arguments.\n", 33), 1);
	if (cub_check(av[1]))
		return (write(1, "Error\nMap is not using .cub extension.\n", 39), 1);
	if (WIN_H < MM_MAXSIZE || WIN_W < MM_MAXSIZE)
		return (printf("Error\nWindow size is undersized.\n"), 1);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (perror("Error\n"), 1);
	return (0);
}

static int	init(t_parse *parse, int fd, t_mlx **mlx, t_cube **cube)
{
	parse = parseinit();
	if (!parse)
		return (parsefree(parse), 1);
	if (parse_filler(fd, parse))
		return (parsefree(parse), 1);
	*mlx = 0;
	if (ft_mlx_start(mlx))
		return (printf("Error\nProblem initialising mlx structs\n"), free(*mlx), parsefree(parse), 1);
	*cube = parse_to_cube(parse, *mlx);
	if (!*cube)
		return (1);
	return (0);
}

static int loop_render(t_cube *cube)
{
	static int i;
	struct timeval time;

	if (!i)
	{
		cube->mlx->image = cube->mlx->img1;
		i++;
	}
	else
	{
		cube->mlx->image = cube->mlx->img2;
		i--;
	}
	gettimeofday(&time, NULL);
	cube->frame = time.tv_sec % 4;
	cube->player[ANGLE] = fix_angle(cube->player[ANGLE]);
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx->mlx, cube->mlx->win, cube->mlx->image->img_ptr, 0, 0);
	moving(cube);
	mouse_rotation(cube);
	return (0);
}

int	main(int ac, char **av)
{
	t_parse	*parse;
	t_cube	*cube;
	t_mlx	*mlx;
	int		fd;

	parse = NULL;
	if (basic_checks(ac, av, &fd) || init(parse, fd, &mlx, &cube))
		return (1);
	mlx_hook(cube->mlx->win, KeyPress, KeyPressMask, &key_press, cube);
	mlx_hook(cube->mlx->win, KeyRelease, KeyReleaseMask, &key_release, cube);
	mlx_hook(cube->mlx->win, 17, 0, &escape, cube);
	mlx_loop_hook(cube->mlx->mlx, &loop_render, cube);
	mlx_loop(cube->mlx->mlx);
	free_cube(cube);
	return (0);
}
