/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:35 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 15:54:43 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static int check_final_elements(t_parse *parse)
{
	if (!parse->textures[NO] || !parse->textures[EA] || !parse->textures[WE])
		return (printf("Error\nMissing basic info\n"), 1);
	if (!parse->textures[SO] || parse->C == -1 || parse->F == -1)
		return (printf("Error\nMissing basic info\n"), 1);
	return (0);
}

static int check_elements(t_parse *parse)
{
	int spritedoor[2];
	int i;
	int j;

	if (parse->player[PLAYER_COUNT] != 1.0)
		return (1);
	spritedoor[0] = 0;
	spritedoor[1] = 0;
	i = 0;
	while (i < parse->height)
	{
		j = 0;
		while (j < parse->width)
		{
			if (parse->map[i][j] == SPRITE)
				spritedoor[0] = 1;
			else if (parse->map[i][j] == DOOR)
				spritedoor[1] = 1;
			j++;
		}
		i++;
	}
	if (!parse->textures[SP] && spritedoor[0])
		return (printf("Error\nMissing sprite textures\n"), 1);
	if (!parse->textures[DO] && spritedoor[1])
		return (printf("Error\nMissing door texture"), 1);
	return (check_final_elements(parse));
}


static int checksides(t_parse *parse, int i, int j)
{
	if (!i || i + 1 == parse->height)
		return (1);
	if (!j || j + 1 == parse->width)
		return (1);
	if (parse->map[i - 1][j] == OUT)
		return (1);
	if (parse->map[i][j - 1] == OUT)
		return (1);
	if (parse->map[i][j + 1] == OUT)
		return (1);
	if (parse->map[i + 1][j] == OUT)
		return (1);
	return (0);
}



int checkmap(t_parse *parse)
{
	int i;
	int j;

	i = 0;
	printmap(parse);
	while (i < parse->height)
	{
		j = 0;
		while (j < parse->width)
		{
			if (parse->map[i][j] == SPACE || parse->map[i][j] == DOOR)
				if (checksides(parse, i, j))
					return (printf("Error\nMap not closed\n"), 1);
			j++;
		}
		i++;
	}
	return (check_elements(parse));
}
