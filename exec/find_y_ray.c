#include "cub3d.h"

typedef struct s_find_y
{
	float	delta;
	float	move_x;
	float	wall_y;
	int		check;
}	t_find_y;

static void	find_y_over_under(t_cube *cube, t_find_y *find, float fixed_angle)
{
	find->move_x = floorf(cube->player[PLAYER_X]);
	find->wall_y = fixed_angle * find->move_x + find->delta;
	find->check = check_wall(find->wall_y, find->move_x - 1, cube);
	while (find->check == 1)
	{
		find->move_x -= 1.0;
		find->wall_y = fixed_angle * find->move_x + find->delta;
		find->check = check_wall(find->wall_y, find->move_x - 1, cube);
	}
}

static void	find_y_else(t_cube *cube, t_find_y *find, float fixed_angle)
{
	find->move_x = ceilf(cube->player[PLAYER_X]);
	find->wall_y = fixed_angle * find->move_x + find->delta;
	find->check = check_wall(find->wall_y, find->move_x, cube);
	while (find->check == 1)
	{
		find->move_x += 1.0;
		find->wall_y = fixed_angle * find->move_x + find->delta;
		find->check = check_wall(find->wall_y, find->move_x, cube);
	}
}

float	find_y_ray(t_cube *cube, float angle, float fixed_angle)
{
	t_find_y	find;

	find.delta = cube->player[PLAYER_Y] - fixed_angle * cube->player[PLAYER_X];
	if (angle < 0.5 || angle > 1.5)
		find_y_over_under(cube, &find, fixed_angle);
	else
		find_y_else(cube, &find, fixed_angle);
	if (find.check == -1)
		return (-1.0);
	cube->ray.h_x = find.move_x;
	if (angle < 0.5 || angle > 1.5)
		cube->ray.h_x -= 1;
	cube->ray.h_y = find.wall_y;
	cube->ray.hity = cube->ray.hit;
	return (sqrt(powf(find.wall_y - cube->player[PLAYER_Y], 2) \
	+ powf(find.move_x - cube->player[PLAYER_X], 2)));
}
