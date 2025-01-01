/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:56:48 by dakojic           #+#    #+#             */
/*   Updated: 2025/01/01 17:54:30 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
// settings check 0
// map      check 1

static void gnlfree(int fd)
{
    char *buf;

    buf = get_next_line(fd);
    while (buf)
    {
        free(buf);
        buf = get_next_line(fd);
    }
    close(fd);
}

char *custom_read(int fd, int check)
{
    char *buf;

    while (1)
    {
        buf = get_next_line(fd);
        if (!buf || check)
            return (buf);
        if (*buf != '\n')
            return (buf);
        free(buf);
    }
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	c = c % 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			ptr = (char *) s + i;
			return ((char *) ptr);
		}
		i++;
	}
	if (s[i] == c)
		return ((char *) s + i);
	ptr = 0;
	return (ptr);
}

char	*ft_substr(char const *s, int start, int len)
{
	int	i;
	int	j;
	char	*copy;
    if(start < 0)
        return (0);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len + start <= ft_strlen(s))
		copy = (char *)malloc(sizeof(char) * (len + 1));
	else
		copy = (char *)malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			copy[j] = s[i];
			j++;
		}
		i++;
	}
	copy[j] = 0;
	return (copy);
}

int settings_split(char *str)
{
    int i;
    i = 2;

    while (str[i])
    {
        if (!ft_strchr(" \t\v\f\r", str[i]))
            return (i);
        i++;
    }
    return (-1);
}

int skip(char *s, int *i)
{
    int com;

    com = 0;
    while (ft_strchr(" \t\v\f\r,", s[*i]))
    {
        if(s[*i] == ',')
            com++;
        (*i)++;
    }
    return (com);
}
int function(char *s)
{
    int i;
    int ret;
    int tmp;

    ret = 0;
    i = 2;
    if (!skip(s, &i) && !s[i])
        return (-1);
    tmp = ft_atoi(s);
    if (tmp < 0 || tmp > 255)
        return (-1);
    ret = tmp << 24;
    if(skip(s, &i) != 1 && !s[i])
        return (-1);
    tmp = ft_atoi(s);
    if (tmp < 0 || tmp > 255)
        return (-1);
    ret |= tmp << 16;
    if(skip(s, &i) != 1 && !s[i])
        return (-1);
    tmp = ft_atoi(s);
    if (tmp < 0 || tmp > 255)
        return (-1);
    ret |= tmp << 8;
    return (ret);
}

int cube_filler2(char *buf, t_cube *cube)
{
    char *tmp;
    
    if (!buf)
        return (1);
    if (ft_strncmp("NO ", buf, 3) && !cube->NO)
        cube->NO = ft_substr(buf, settings_split(buf), ft_strchr(buf, '\n'));
    else if (ft_strncmp("WE ", buf, 3) && !cube->WE)
        cube->WE = ft_substr(buf, settings_split(buf), ft_strchr(buf, '\n'));
    else if (ft_strncmp("SO ", buf, 3) && !cube->SO)
        cube->SO = ft_substr(buf, settings_split(buf), ft_strchr(buf, '\n'));
    else if (ft_strncmp("EA ", buf, 3) && !cube->EA)
        cube->EA = ft_substr(buf, settings_split(buf), ft_strchr(buf, '\n'));
    else if (ft_strncmp("F ", buf, 2) && !cube->F)
        cube->F = function(buf);
    else if (ft_strncmp("C ", buf, 2) && !cube->C)
        cube->C = function(buf);
    else
        return (1);
    return (0);
}

int cube_filler(int fd, t_cube *cube)
{
    char *buff;
    int i;

    buff = custom_read(fd, 0);
    if(cube_filler2(buff, cube))
        return (gnlfree(fd) ,1);
    buff = custom_read(fd, 0);
    if(cube_filler2(&buff, &cube))
        return (gnlfree(fd) ,1);
    buff = custom_read(fd, 0);
    if(cube_filler2(&buff, &cube))
        return (gnlfree(fd) ,1);
    buff = custom_read(fd, 0);
    if(cube_filler2(&buff, &cube))
        return (gnlfree(fd) ,1);    
    buff = custom_read(fd, 0);
    if(cube_filler2(&buff, &cube))
        return (gnlfree(fd) ,1);
    return (gnlfree(fd) ,0);
}

int main(int ac, char **av)
{
    t_cube *cube;
    int fd;

    if(ac != 2)
        return (error("Wrong number of arguments.\n"), 1);
    if(!cub_check(av[1]))
        return (error("Map is not using .cub extension.\n"), 1);
    fd = open(av[1]);
    if (fd == -1)
        return (perror("Open"), 1);
    cube = ft_calloc(sizeof(cube), 1);
    if(!cube || cube_filler(fd, cube))
        return (1);



    null_cube(&cube);
    return (0);
}