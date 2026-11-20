#include "cub3d.h"

void	display_pix(t_img_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->adress + (y * img->size + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

void	cb_putpixel(int i, t_cube *cube, int color, int flag)
{
	if (flag)
	{
		if (cube->ray.index < 0 || cube->ray.index >= WIN_W || \
			i > WIN_H || i < 0)
			return ;
		if (cube->ray.index <= (MM_SIZE * 9) && i <= (MM_SIZE * 9))
			return ;
	}
	display_pix(cube->mlx->image, cube->ray.index, i, color);
}

void	draw_other(float top, t_cube *cube)
{
	int	i;

	i = 0;
	while (i < top)
	{
		cb_putpixel(i, cube, cube->data.fc[1], 1);
		i++;
	}
	if (i >= 1)
		i--;
	while (i < WIN_H)
	{
		cb_putpixel(i, cube, cube->data.fc[0], 1);
		i++;
	}
}

void	draw_wall_other(t_cube *cube, float pixel, float offset, int i)
{
	int		k;
	float	stat;
	float	l;

	stat = cube->ray.texture->pix_h * pixel ;
	k = (int)floor(offset * cube->ray.texture->pix_w);
	l = 0;
	while (l < cube->ray.texture->pix_h)
	{
		cb_putpixel(i, cube, \
			cube->ray.adress[cube->ray.texture->pix_w * (int)floor(l) + k], 1);
		l += stat;
		i++;
	}
}

void	draw_wall(float top_pixel, t_cube *cube, float offset)
{
	int		i;
	int		k;
	float	l;
	float	scale;

	i = 0;
	k = (int)(offset * cube->ray.texture->pix_w);
	l = top_pixel * cube->ray.texture->pix_h;
	scale = ((1 - 2 * top_pixel) / WIN_H) * cube->ray.texture->pix_h;
	while (i < WIN_H)
	{
		cb_putpixel(i, cube, \
			cube->ray.adress[cube->ray.texture->pix_w * (int)(l) + k], 1);
		l += scale;
		i++;
	}
}
