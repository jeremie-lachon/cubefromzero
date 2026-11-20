#include "cub3d.h"

int	intfree(int ***array, int i)
{
	int	j;

	if (!*array)
		return (1);
	j = 0;
	while (j < i)
		free((*array)[j++]);
	free(*array);
	*array = 0;
	return (0);
}

int	parsefree(t_parse *parse)
{
	int	i;

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

int	cb_clear_display(t_mlx *mlx)
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

int	free_cube(t_cube *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (i < 5)
	{
		if (c->texture[i] && c->texture[i]->img_ptr)
			mlx_destroy_image(c->mlx->mlx, c->texture[i]->img_ptr);
		free(c->texture[i++]);
	}
	while (c->sprite && c->nsprite-- > 0)
	{
		if (c->sprite[c->nsprite] && c->sprite[c->nsprite]->img_ptr)
			mlx_destroy_image(c->mlx->mlx, c->sprite[c->nsprite]->img_ptr);
		free(c->sprite[c->nsprite]);
	}
	free(c->sprite);
	i = 0;
	while (i < c->data.map_h)
		free(c->data.map[i++]);
	free(c->data.map);
	cb_clear_display(c->mlx);
	free(c);
	return (0);
}
