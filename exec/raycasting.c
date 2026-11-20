#include "cub3d.h"

typedef struct s_rayparam
{
	float	fixed_angle[2];
	float	angle;
	float	temp[2];
}	t_rayparam;

static void	rays(t_rayparam *r, t_cube *cube)
{
	r->temp[0] = find_x_ray(cube, r->angle, r->fixed_angle[0]);
	r->temp[1] = find_y_ray(cube, r->angle, r->fixed_angle[0]);
	wall_check(r->temp, cube, r->angle, r->fixed_angle[1]);
	cube->ray.index++;
}

static void	angle_setter(t_rayparam *r, t_cube *cube, float *aux_var)
{
	if (cube->ray.index < (WIN_W / 2))
	{
		*aux_var = atanf(((WIN_W / 2) - (float)cube->ray.index) / \
		((WIN_W / 2) / tanf((FOV_W / 360.F) * PI)));
		r->angle = (FOV_W / 360.F) * PI - *aux_var;
		r->angle = fix_angle(cube->player[ANGLE] - \
			(FOV_W / 360.F) + r->angle / PI);
	}
	else
	{
		*aux_var = atanf(((float)cube->ray.index - (WIN_W / 2)) / \
		((WIN_W / 2) / tanf((FOV_W / 360.F) * PI)));
		r->angle = fix_angle(cube->player[ANGLE] + *aux_var / PI);
	}
	r->fixed_angle[1] = cosf(*aux_var);
}

void	raycasting(t_cube *cube)
{
	t_rayparam	r;
	float		aux_var;

	cube->ray.index = 0;
	r.angle = fix_angle(cube->player[ANGLE] - (FOV_W / 360.F));
	while (cube->ray.index < WIN_W)
	{
		angle_setter(&r, cube, &aux_var);
		if (r.angle > 1)
		{
			if (r.angle < 1.5)
				r.fixed_angle[0] = tanf((r.angle - 1.F) * -PI);
			else
				r.fixed_angle[0] = tanf((2.F - r.angle) * PI);
		}
		else
		{
			if (r.angle > 0.5)
				r.fixed_angle[0] = tanf((1 - r.angle) * PI);
			else
				r.fixed_angle[0] = tanf(r.angle * -PI);
		}
		rays(&r, cube);
	}
	minimap_display(cube);
}
