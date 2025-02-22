/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:53:49 by snek              #+#    #+#             */
/*   Updated: 2025/02/22 02:11:24 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WH " \t\v\f\r\n"

static int	get_color(char *s, int i, int ret)
{
	int	tmp;

	if (skip(s, &i, 0) || !s[i])
		return (-1);
	tmp = ft_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret = tmp << 16;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = ft_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret |= tmp << 8;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = ft_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	if (skip(s, &i, 1) || s[i] != '\n')
		return (-1);
	ret |= tmp;
	return (ret);
}

static int	parse_filler3(char *buf, t_parse *cube, int tmp)
{
	if (!strncmp("EA ", buf, 3) && !cube->textures[EA])
		cube->textures[EA] = ft_strtrim(ft_substr(buf, sett(buf), tmp), WH);
	else if (!strncmp("F ", buf, 2) && cube->f == -1)
		cube->f = get_color(buf, 1, 0);
	else if (!strncmp("C ", buf, 2) && cube->c == -1)
		cube->c = get_color(buf, 1, 0);
	else if (!strncmp("DO ", buf, 3) && !cube->textures[DO])
		cube->textures[DO] = ft_strtrim(ft_substr(buf, sett(buf), tmp), WH);
	else if (!strncmp("SP ", buf, 3) && !cube->textures[SP])
		cube->textures[SP] = ft_strtrim(ft_substr(buf, sett(buf), tmp), WH);
	else
		return (2);
	return (free(buf), 0);
}

int	parse_filler2(char *buf, t_parse *cube)
{
	int	tmp;

	if (!buf)
		return (1);
	if (*buf == '\n')
		return (free(buf), 0);
	if (!ft_strchr(buf, '\n'))
		return (1);
	tmp = ft_strchr(buf, '\n') - buf - 3;
	if (!strncmp("NO ", buf, 3) && !cube->textures[NO])
		cube->textures[NO] = ft_strtrim(ft_substr(buf, sett(buf), tmp), WH);
	else if (!strncmp("WE ", buf, 3) && !cube->textures[WE])
		cube->textures[WE] = ft_strtrim(ft_substr(buf, sett(buf), tmp), WH);
	else if (!strncmp("SO ", buf, 3) && !cube->textures[SO])
		cube->textures[SO] = ft_strtrim(ft_substr(buf, sett(buf), tmp), WH);
	else
		return (parse_filler3(buf, cube, tmp));
	return (free(buf), 0);
}
