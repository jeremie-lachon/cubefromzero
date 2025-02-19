/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:26:13 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/19 17:08:16 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void display_pix(t_img_data *img, int x, int y, int color)
{
	char *dest;
	dest = img->adress + (y * img->size + x  * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

void ft_putpixel(int ray, int i, t_cube *cube, int color, int flag)
{
	if(flag)
	{
		if (ray < 0 || ray >= WIN_W || i > WIN_H || i < 0)
			return ;
		if(ray <= cube->minimap_w && i <= cube->minimap_h)
			return ;
	}
	display_pix(cube->mlx->image, ray, i, color);
}

void draw_other(float top, t_cube *cube)
{
	int i;

	i = 0;
	while(i < top)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->data.FC[1], 1);
		i++;
	}
	if(i >= 1)
		i--;
	while(i < WIN_H)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->data.FC[0], 1);
		i++;
	}
}

void draw_wall_other(t_cube *cube, float pixel, float offset, int i)
{
	int		k;
	float	stat;
	float	l;

	stat = cube->ray.texture->pix_h * pixel ;
	k = (int)floor(offset * cube->ray.texture->pix_w);
	l = 0;
	while(l < cube->ray.texture->pix_h)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->ray.adress[cube->ray.texture->pix_w  * (int)floor(l) + k], 1);
		l += stat;
		i++;
	}
}

void draw_wall(float top_pixel, t_cube *cube, float offset)
{
	int i;
	int k;
	float l;
	float scale;

	i = 0;
	k = (int)(offset * cube->ray.texture->pix_w);
	l = top_pixel * cube->ray.texture->pix_h;
	scale = ((1 - 2 * top_pixel) / WIN_H) * cube->ray.texture->pix_h;
	while(i < WIN_H)
	{
		ft_putpixel(cube->ray.index, i, cube, cube->ray.adress[cube->ray.texture->pix_w  * (int)(l)  + k], 1);
		l += scale;
		i++;
	}
}
