#include "cub3d.h"

float	fix_angle(float angle)
{
	while (angle > 2.F)
		angle -= 2;
	while (angle < 0)
		angle += 2;
	return (angle);
}

float	added_angle(t_cube *cube)
{
	int	hor;
	int	ver;

	hor = 0;
	ver = 0;
	if (cube->input[KEY_W])
		ver++;
	if (cube->input[KEY_S])
		ver--;
	if (cube->input[KEY_A])
		hor--;
	if (cube->input[KEY_D])
		hor++;
	if (!hor && !ver)
		return (-1);
	if (hor && ver)
		return ((ver + 2) * hor * 0.25);
	return (hor * 0.5 + (ver + 1) / 2);
}
