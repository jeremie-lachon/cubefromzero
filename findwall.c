/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:54:53 by jla-chon          #+#    #+#             */
/*   Updated: 2024/12/31 16:41:28 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int player_filler(t_cube *cube)
{
	float fov_rad;

	if(cube->data.facing == 'N')
        cube->player.angle = 0.5;
	if(cube->data.facing == 'S')
        cube->player.angle = 1.5;
	if(cube->data.facing == 'E')
        cube->player.angle = 0;
	if(cube->data.facing == 'W')
        cube->player.angle = 1;
	// cube->player.fov_rad = FOV;
	// fov_rad = cube->player.fov_rad;
	cube->player.x = cube->data.pos_x * CELL_SIZE + CELL_SIZE / 2;
	cube->player.y = cube->data.pos_y * CELL_SIZE + CELL_SIZE / 2;
	return (0);
}

static float	findwall(t_cube *cube, int i, float angle)
{
	float	dist1;
	float	dist2;

	



	if (dist1 > dist2)
		return (dist2);
	return (dist1);
}

static void fill(t_cube *cube)
{
	int	i;
	static float unit;
	float	wall;

	if (!unit)
		unit = FOV / WIN_W;
	i = 0;
	while (i < WIN_W)
	{
		wall = findwall(cube, i, unit * i);
		// drawwall();
		i++;
	}
}

int	main(void)
{
	t_cube	cube;

	cube = (t_cube){0};
	map_filler(&cube.data);
	player_filler(&cube);
}
