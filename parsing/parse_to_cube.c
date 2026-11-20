#include "cub3d.h"

static void	freecubetext(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		free(cube->texture[i]);
		cube->texture[i++] = 0;
	}
}

static t_cube	*cb_cube_init(void)
{
	t_cube	*cube;
	int		i;

	i = 0;
	cube = cb_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (perror("Error\n"), NULL);
	while (i < 5)
	{
		cube->texture[i] = cb_calloc(sizeof(t_img_data), 1);
		if (!cube->texture[i++])
			return (perror("Error\n"), freecubetext(cube), free(cube), NULL);
	}
	return (cube);
}

static int	fillsides(t_cube *cube, t_parse *parse, t_mlx *mlx)
{
	if (imgstruct(cube, NO, mlx, parse))
		return (1);
	if (imgstruct(cube, WE, mlx, parse))
		return (1);
	if (imgstruct(cube, SO, mlx, parse))
		return (1);
	if (imgstruct(cube, EA, mlx, parse))
		return (1);
	if (parse->textures[DO] && imgstruct(cube, DO, mlx, parse))
		return (1);
	return (0);
}

t_cube	*parse_to_cube(t_parse *parse, t_mlx *mlx)
{
	t_cube	*cube;

	cube = cb_cube_init();
	if (!cube)
		return (parsefree(parse), cb_clear_display(mlx), NULL);
	cube->mlx = mlx;
	cube->data.map = parse->map;
	parse->map = 0;
	cube->data.map_w = parse->width;
	cube->data.map_h = parse->height;
	cube->data.fc[0] = parse->f;
	cube->data.fc[1] = parse->c;
	cube->player[PLAYER_X] = parse->player[PLAYER_X];
	cube->player[PLAYER_Y] = parse->player[PLAYER_Y];
	cube->player[ANGLE] = parse->player[ANGLE];
	if (fillsides(cube, parse, cube->mlx))
		return (printf("Error\nProblem converting \
			wall/door images to mlx_img\n"), \
		free_cube(cube), parsefree(parse), NULL);
	if (fillsprite(parse, cube, cube->mlx))
		return (freetexts(cube), \
		printf("Error\nProblem converting sprite images to mlx_img\n"), \
		free_cube(cube), parsefree(parse), NULL);
	return (parsefree(parse), cube);
}
