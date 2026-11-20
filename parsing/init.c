#include "cub3d.h"

static void	freesprite(t_img_data **sprite, int n, t_mlx *mlx)
{
	int	j;

	if (!sprite)
		return ;
	j = 0;
	while (j < n)
	{
		if (sprite[j])
			mlx_destroy_image(mlx->mlx, sprite[j]->img_ptr);
		free(sprite[j]);
		sprite[j++] = 0;
	}
}

static int	starter(int *n, t_cube *cube, char ***all, t_parse *parse)
{
	*all = cb_split(parse->textures[SP], ' ');
	if (!*all)
		return (1);
	*n = 0;
	while ((*all)[(*n)])
		(*n)++;
	cube->sprite = cb_calloc(*n, sizeof(t_img_data *));
	if (!cube->sprite)
		return (cb_freesplit(*all, *n), 1);
	cube->nsprite = *n;
	*n = 0;
	return (0);
}

int	fillsprite(t_parse *p, t_cube *c, t_mlx *m)
{
	int		n;
	char	**all;

	if (!p->textures[SP])
		return (0);
	if (starter(&n, c, &all, p))
		return (1);
	while (n < c->nsprite)
	{
		c->sprite[n] = cb_calloc(sizeof(t_img_data), 1);
		if (!c->sprite[n])
			return (freesprite(c->sprite, n, m), \
			cb_freesplit(all, c->nsprite), 1);
		c->sprite[n]->img_ptr = mlx_xpm_file_to_image(m->mlx, all[n], \
			&c->sprite[n]->pix_w, &c->sprite[n]->pix_h);
		if (!c->sprite[n]->img_ptr)
			return (freesprite(c->sprite, n, m), \
			cb_freesplit(all, c->nsprite), 1);
		c->sprite[n]->adress = mlx_get_data_addr(c->sprite[n]->img_ptr, \
			&c->sprite[n]->bpp, &c->sprite[n]->size, &c->sprite[n]->endl);
		if (!c->sprite[n]->adress)
			return (cb_freesplit(all, c->nsprite), 1);
		n++;
	}
	return (cb_freesplit(all, c->nsprite), 0);
}
