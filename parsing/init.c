/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:35:14 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/20 16:20:57 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void freesprite(t_img_data **sprite, int n, t_mlx *mlx)
{
	int j;

	if (!sprite)
		return;
	j = 0;
	while (j < n)
	{
		if (sprite[j])
			mlx_destroy_image(mlx->mlx, sprite[j++]->img_ptr);
	}
}

static int starter(int *n, t_cube *cube, char ***all, t_parse *parse)
{
    *all = ft_split(parse->textures[SP], ' ');
	if (!*all)
		return (1);
    *n = 0;
	while ((*all)[(*n)])
		(*n)++;
	cube->sprite = ft_calloc(*n, sizeof(t_img_data *));
	if (!cube->sprite)
		return (ft_freesplit(*all, *n), 1);
	cube->nsprite = *n;
	*n = 0;
    return (0);
}

int fillsprite(t_parse *parse, t_cube *cube, t_mlx *mlx)
{
	int n;
	char **all;

	if (!parse->textures[SP])
		return (0);
	if(starter(&n, cube, &all, parse))
        return (1);
	while (n < cube->nsprite)
	{
		cube->sprite[n] = ft_calloc(sizeof(t_img_data), 1);
		if (!cube->sprite[n])
			return (freesprite(cube->sprite, n, mlx), ft_freesplit(all, n), 1);
		cube->sprite[n]->img_ptr = mlx_xpm_file_to_image(mlx->mlx, all[n], &cube->sprite[n]->pix_w, &cube->sprite[n]->pix_h);
		if (!cube->sprite[n]->img_ptr)
			return (freesprite(cube->sprite, n, mlx), ft_freesplit(all, n), 1);
		cube->sprite[n]->adress = mlx_get_data_addr(cube->sprite[n]->img_ptr, &cube->sprite[n]->bpp, &cube->sprite[n]->size, &cube->sprite[n]->endl);
		if (!cube->sprite[n]->adress)
			return (freesprite(cube->sprite, n, mlx), ft_freesplit(all, n), 1);
		n++;
	}
	return (ft_freesplit(all, n), 0);
}