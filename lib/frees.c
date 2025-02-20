/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:01:45 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/20 11:48:29 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int intfree(int ***array, int i)
{
	int j;

	if (!*array)
		return (1);
	j = 0;
	while (j < i)
		free((*array)[j++]);
	free(*array);
	*array = 0;
	return (0);
}

int parsefree(t_parse *parse)
{
	int i;

	i = 0;
	if (!parse)
		return (0);
	if (parse->map)
	{
		while (i < parse->height)
		{
			free(parse->map[i]);
			i++;
		}
		free(parse->map);
	}
	i = 0;
	while (i < 6)
		free(parse->textures[i++]);
	free(parse->textures);
	free(parse);
	return (0);
}

int ft_clear_display(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img1->img_ptr);
	mlx_destroy_image(mlx->mlx, mlx->img2->img_ptr);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->img1);
	free(mlx->img2);
	free(mlx->mlx);
	free(mlx);
	return (0);
}

int free_cube(t_cube *cube)
{
	int i;

	i = 0;
	if (!cube)
		return (0);
	while (i < 5)
	{
		if (cube->texture[i] && cube->texture[i]->img_ptr)
			mlx_destroy_image(cube->mlx->mlx, cube->texture[i]->img_ptr);
		free(cube->texture[i++]);
	}
	while (cube->sprite && cube->nsprite-- > 0)
	{
		if (cube->sprite[cube->nsprite] && cube->sprite[cube->nsprite]->img_ptr)
			mlx_destroy_image(cube->mlx->mlx, cube->sprite[cube->nsprite]->img_ptr);
		free(cube->sprite[cube->nsprite]);
	}
	free(cube->sprite);
	i = 0;
	while (i < cube->data.map_h)
		free(cube->data.map[i++]);
	free(cube->data.map);
	ft_clear_display(cube->mlx);
	free(cube);
	return (0);
}