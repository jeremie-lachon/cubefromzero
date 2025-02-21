/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:24:03 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 15:24:44 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	display_pix2(t_img_data *img, int x, int y, int color)
// {
// 	char	*dest;

// 	dest = img->adress + (y * img->size + x * (img->bpp / 8));
// 	*(unsigned int *)dest = color;
// }

static void	ft_putpixel2(int ray, int i, t_cube *cube, int flag)
{
	if (flag)
	{
		if (ray < 0 || ray >= WIN_W || \
			i > WIN_H || i < 0)
			return ;
		if (ray <= cube->minimap_w && i <= cube->minimap_h)
			return ;
	}
	display_pix(cube->mlx->image, ray, i, 0xea0000);
}

static void draw_map_line(t_cube *cube, int x)
{
	int y;

	y = 0;
	while (y < cube->minimap_h)
	{
		ft_putpixel2(x, y, cube, 0);
		y++;
	}
}

void draw_minimap(t_cube *cube)
{
	int i;

	i = 0;
	while (i < cube->minimap_w)
	{
		draw_map_line(cube, i);
		i++;
	}
}