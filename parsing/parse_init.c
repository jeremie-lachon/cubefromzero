#include "cub3d.h"

t_parse	*parseinit(void)
{
	t_parse	*parse;

	parse = cb_calloc(sizeof(t_parse), 1);
	if (!parse)
		return (perror("Error\n"), NULL);
	parse->textures = cb_calloc(sizeof(char *), 6);
	if (!parse->textures)
		return (perror("Error\n"), free(parse), NULL);
	parse->c = -1;
	parse->f = -1;
	return (parse);
}
