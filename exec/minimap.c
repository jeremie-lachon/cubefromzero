#include "cub3d.h"

typedef struct s_mini
{
	int	i;
	int	j;
	int	x_place;
	int	y_place;
	int	sprite;
	int	x;
	int	y;
}	t_mini;

static void	draw_pixel_map(int x, int y, t_cube *cube, int sprite)
{	
	int	i;
	int	j;

	i = 0;
	if (sprite == SPACE)
		sprite = 0xffffff;
	else if (sprite == WALL)
		sprite = 0x1e17fb;
	else if (sprite == OUT)
		sprite = 0xffffff;
	else if (sprite == DOOR)
		sprite = 0xA04000;
	else
		sprite = 0x00ff00;
	while (i < MM_SIZE)
	{
		j = 0;
		while (j < MM_SIZE)
		{
			display_pix(cube->mlx->image, x + i, y + j, sprite);
			j++;
		}
		i++;
	}
}

void	mini_draw(t_mini *m, t_cube *cube)
{
	m->x = m->x_place + m->i;
	m->y = m->y_place + m->j;
	if (m->x < 0 || m->x >= cube->data.map_w)
		m->sprite = OUT;
	else if (m->y < 0 || m->y >= cube->data.map_h)
		m->sprite = OUT;
	else
		m->sprite = cube->data.map[m->y][m->x];
	draw_pixel_map((8 - m->i) * MM_SIZE, m->j * MM_SIZE, cube, m->sprite);
}

void	minimap_display(t_cube *cube)
{
	t_mini	m;

	m.x_place = (int)cube->player[PLAYER_X] - 4;
	m.y_place = (int)cube->player[PLAYER_Y] - 4;
	m.i = -1;
	while (++m.i < 9)
	{
		m.j = -1;
		while (++m.j < 9)
		{
			mini_draw(&m, cube);
		}
	}
	m.i = MM_SIZE * 4;
	while (m.i < MM_SIZE * 5)
	{
		m.j = MM_SIZE * 4;
		while (m.j < MM_SIZE * 5)
		{
			display_pix(cube->mlx->image, m.i, m.j, 0);
			m.j++;
		}
		m.i++;
	}
}
