/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:28:00 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 18:11:08 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freetexts(t_cube *cube)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		if (j < 5 && cube->texture[j]->img_ptr)
			mlx_destroy_image(cube->mlx->mlx, cube->texture[j]->img_ptr);
		free(cube->texture[j]);
		cube->texture[j++] = 0;
	}
}

int	imgstruct(t_cube *c, int num, t_mlx *mlx, t_parse *p)
{
	c->texture[num]->img_ptr = mlx_xpm_file_to_image(mlx->mlx, \
		p->textures[num], \
		&c->texture[num]->pix_w, &c->texture[num]->pix_h);
	if (!c->texture[num]->img_ptr)
		return (freetexts(c), 1);
	c->texture[num]->adress = mlx_get_data_addr(c->texture[num]->img_ptr, \
	&c->texture[num]->bpp, &c->texture[num]->size, &c->texture[num]->endl);
	if (!c->texture[num]->adress)
		return (freetexts(c), 1);
	return (0);
}

static t_mlx	*ft_mlx_init(void)
{
	t_mlx	*mlx;

	mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!mlx)
		return (NULL);
	mlx->img1 = ft_calloc(sizeof(t_img_data), 1);
	if (!mlx->img1)
		return (free(mlx), NULL);
	mlx->img2 = ft_calloc(sizeof(t_img_data), 1);
	if (!mlx->img2)
		return (free(mlx->img1), free(mlx), NULL);
	return (mlx);
}

void	destroyer(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img1->img_ptr);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
}

int	ft_mlx_start(t_mlx **mlx_address)
{
	t_mlx	*mlx;

	mlx = ft_mlx_init();
	if (!mlx)
		return (1);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cube");
	if (!mlx->win)
		return (mlx_destroy_display(mlx->mlx), 1);
	mlx->img1->img_ptr = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (!mlx->img1)
		return (mlx_destroy_window(mlx->mlx, mlx->win), \
		mlx_destroy_display(mlx->mlx), 1);
	mlx->img1->adress = mlx_get_data_addr(mlx->img1->img_ptr, \
		&mlx->img1->bpp, &mlx->img1->size, &mlx->img1->endl);
	mlx->img2->img_ptr = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (!mlx->img2)
		return (destroyer(mlx), 1);
	mlx->img2->adress = mlx_get_data_addr(mlx->img2->img_ptr, \
		&mlx->img2->bpp, &mlx->img2->size, &mlx->img2->endl);
	*mlx_address = mlx;
	return (0);
}
