/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:13:53 by jla-chon          #+#    #+#             */
/*   Updated: 2025/01/01 18:13:37 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct s_map
{
	int	**map;
	int	xmax;
	int	ymax;
}	t_map;

typedef struct s_texture
{
	t_img_data	sides[4];
	int			ceiling;
	int			floor;
}	t_texture;

typedef struct s_list
{
	struct s_list *next;
	void *data;
}t_list;

t_cube	*fillinfo(char *file)
{
	int	fd;
	t_cube *cube;
	char	*gnl;

	fd = open(file, O_RDONLY, 0);
	gnl = get_next_line(fd);
	while (gnl)
	{
		
		free(gnl);
	}
	return (close(fd), cube);
}
