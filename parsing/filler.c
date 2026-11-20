#include "cub3d.h"

#define WH " \t\v\f\r\n"

static int	get_color(char *s, int i, int ret)
{
	int	tmp;

	if (skip(s, &i, 0) || !s[i])
		return (-1);
	tmp = cb_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret = tmp << 16;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = cb_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	ret |= tmp << 8;
	if (skip(s, &i, 1) != 1 || !s[i])
		return (-1);
	tmp = cb_atoi(s + i);
	if (tmp < 0 || tmp > 255)
		return (-1);
	if (skip(s, &i, 1) || s[i] != '\n')
		return (-1);
	ret |= tmp;
	return (ret);
}

static int	parse_filler3(char *buf, t_parse *cube, int tmp)
{
	if (!cb_strncmp("EA ", buf, 3) && !cube->textures[EA])
		cube->textures[EA] = cb_strtrim(cb_substr(buf, sett(buf), tmp), WH);
	else if (!cb_strncmp("F ", buf, 2) && cube->f == -1)
		cube->f = get_color(buf, 1, 0);
	else if (!cb_strncmp("C ", buf, 2) && cube->c == -1)
		cube->c = get_color(buf, 1, 0);
	else if (!cb_strncmp("DO ", buf, 3) && !cube->textures[DO])
		cube->textures[DO] = cb_strtrim(cb_substr(buf, sett(buf), tmp), WH);
	else if (!cb_strncmp("SP ", buf, 3) && !cube->textures[SP])
		cube->textures[SP] = cb_strtrim(cb_substr(buf, sett(buf), tmp), WH);
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
	if (!cb_strchr(buf, '\n'))
		return (1);
	tmp = cb_strchr(buf, '\n') - buf - 3;
	if (!cb_strncmp("NO ", buf, 3) && !cube->textures[NO])
		cube->textures[NO] = cb_strtrim(cb_substr(buf, sett(buf), tmp), WH);
	else if (!cb_strncmp("WE ", buf, 3) && !cube->textures[WE])
		cube->textures[WE] = cb_strtrim(cb_substr(buf, sett(buf), tmp), WH);
	else if (!cb_strncmp("SO ", buf, 3) && !cube->textures[SO])
		cube->textures[SO] = cb_strtrim(cb_substr(buf, sett(buf), tmp), WH);
	else
		return (parse_filler3(buf, cube, tmp));
	return (free(buf), 0);
}
