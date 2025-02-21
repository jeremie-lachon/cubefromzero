/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:31:15 by dakojic           #+#    #+#             */
/*   Updated: 2025/02/21 15:31:23 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse *parseinit(void)
{
	t_parse *parse;

	parse = ft_calloc(sizeof(t_parse), 1);
	if (!parse)
		return (perror("Error\n"), NULL);
	parse->textures = ft_calloc(sizeof(char *), 6);
	if (!parse->textures)
		return (perror("Error\n"), free(parse), NULL);
	parse->C = -1;
	parse->F = -1;
	return (parse);
}