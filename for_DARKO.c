/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_DARKO.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:53:49 by snek              #+#    #+#             */
/*   Updated: 2025/02/21 14:13:23 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WH " \t\v\f\r\n"

static int	parse_filler3(char *buf, t_parse *cube, char *tmp, char *tmp2)
{
	if (!strncmp("EA ", buf, 3) && !cube->textures[EA])
		cube->textures[EA] = ft_strtrim(ft_substr(buf, sett(buf), tmp2), WH);
	else if (!strncmp("F ", buf, 2) && cube->F == -1)
		cube->F = function(buf);
	else if (!strncmp("C ", buf, 2) && cube->C == -1)
		cube->C = function(buf);
	else if (!strncmp("DO ", buf, 3) && !cube->textures[DO])
		cube->textures[DO] = ft_strtrim(ft_substr(buf, sett(buf), tmp2), WH);
	else if (!strncmp("SP ", buf, 3) && !cube->textures[SP])
		cube->textures[SP] = ft_strtrim(ft_substr(buf, sett(buf), tmp2), WH);
	else
		return (2);
	return (free(buf), 0);
}

int	parse_filler2(char *buf, t_parse *cube)
{
	char	*tmp;
	char	*tmp2;

	if (!buf)
		return (1);
	if (*buf == '\n')
		return (free(buf), 0);
	tmp = ft_strchr(buf, '\n');
	if (!tmp)
		return (1);
	tmp2 = tmp - buf - 3;
	if (!strncmp("NO ", buf, 3) && !cube->textures[NO])
		cube->textures[NO] = ft_strtrim(ft_substr(buf, sett(buf), tmp2), WH);
	else if (!strncmp("WE ", buf, 3) && !cube->textures[WE])
		cube->textures[WE] = ft_strtrim(ft_substr(buf, sett(buf), tmp2), WH);
	else if (!strncmp("SO ", buf, 3) && !cube->textures[SO])
		cube->textures[SO] = ft_strtrim(ft_substr(buf, sett(buf), tmp2), WH);
	else
		return (parse_filler3(buf, cube, tmp, tmp2));
	return (free(buf), 0);
}
