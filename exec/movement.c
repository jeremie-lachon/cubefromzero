/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:26:24 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 17:21:13 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_moves
{
	int		map_grid_y;
	int		map_grid_x;
	float	new_x;
	float	new_y;
}	t_moves;

static void	new_xy(t_cube *cube, t_moves *m, float angle)
{
	m->new_x = (cube->player[PLAYER_X] + (cos(angle) / 50));
	m->new_y = (cube->player[PLAYER_Y] - (sin(angle) / 50));
	m->map_grid_x = ((int)m->new_x);
	if (m->map_grid_x > cube->data.map_w)
		m->map_grid_x = cube->data.map_w;
	m->map_grid_y = ((int)m->new_y);
	if (m->map_grid_y > cube->data.map_h)
		m->map_grid_y = cube->data.map_h;
}

static void	true_move(t_cube *cube, t_moves *m)
{
	if (cube->data.map[m->map_grid_y][(int)cube->player[PLAYER_X]] == WALL || \
	cube->data.map[m->map_grid_y][(int)cube->player[PLAYER_X]] == SPRITE)
	{
		if (m->map_grid_y == cube->player[PLAYER_Y])
			;
		else if (m->map_grid_y < cube->player[PLAYER_Y])
			cube->player[PLAYER_Y] = m->map_grid_y + 1.001;
		else
			cube->player[PLAYER_Y] = m->map_grid_y - 0.001;
	}
	else
		cube->player[PLAYER_Y] = m->new_y;
	if (cube->data.map[(int)cube->player[PLAYER_Y]][m->map_grid_x] == WALL || \
	cube->data.map[(int)cube->player[PLAYER_Y]][m->map_grid_x] == SPRITE)
	{
		if (m->map_grid_x == cube->player[PLAYER_X])
			;
		else if (m->map_grid_x < cube->player[PLAYER_X])
			cube->player[PLAYER_X] = m->map_grid_x + 1.001;
		else
			cube->player[PLAYER_X] = m->map_grid_x - 0.001;
	}
	else
		cube->player[PLAYER_X] = m->new_x;
}

static void	move_player(t_cube *cube, float angle)
{
	t_moves	m;

	new_xy(cube, &m, angle);
	true_move(cube, &m);
}

void	moving(t_cube *cube)
{
	float	angle;

	if (cube->input[KEY_LEFT] || cube->input[MOUSE_LEFT])
		cube->player[ANGLE] += ROTATION_SPEED;
	if (cube->input[KEY_RIGHT] || cube->input[MOUSE_RIGHT])
		cube->player[ANGLE] -= ROTATION_SPEED;
	angle = added_angle(cube);
	if (angle != -1)
		move_player(cube, fix_angle(angle + cube->player[ANGLE]) * PI);
}

void	mouse_rotation(t_cube *cube)
{
	mlx_mouse_get_pos(cube->mlx->mlx, cube->mlx->win, \
		&cube->mouse_x, &cube->mouse_y);
	if (cube->mouse_x < 0 || cube->mouse_x > WIN_W || \
		cube->mouse_y < 0 || cube->mouse_y > WIN_H)
		cube->mouse_x = (WIN_W / 2);
	if (cube->mouse_x > (WIN_W / 2) + 150)
		cube->input[MOUSE_LEFT] = 1;
	else
		cube->input[MOUSE_LEFT] = 0;
	if (cube->mouse_x < (WIN_W / 2) - 150)
		cube->input[MOUSE_RIGHT] = 1;
	else
		cube->input[MOUSE_RIGHT] = 0;
}
