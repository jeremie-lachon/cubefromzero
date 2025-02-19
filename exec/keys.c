/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:54:33 by snek              #+#    #+#             */
/*   Updated: 2025/02/05 16:56:42 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	escape(t_cube *cube)
{
	free_cube(cube);
	exit(0);
}

int key_press(int keysym, t_cube *cube)
{

	if (keysym == XK_Escape)
		escape(cube);
	if(keysym == XK_w)
	{	
		cube->input[KEY_W] = 1;
	}
	if(keysym == XK_s)
		cube->input[KEY_S] = 1;
	if(keysym == XK_d)
		cube->input[KEY_A] = 1;
	if(keysym == XK_a)
		cube->input[KEY_D] = 1;
	if (keysym == XK_Right)
		cube->input[KEY_LEFT] = 1;
	if (keysym == XK_Left)
		cube->input[KEY_RIGHT] = 1;
	return (0);
}

int key_release(int keysym, t_cube *cube)
{
	if(keysym == 3)
		cube->input[MOUSE_LEFT] = 0;
	if(keysym == XK_w)
		cube->input[KEY_W] = 0;
	if(keysym == XK_s)
		cube->input[KEY_S] = 0;
	if(keysym == XK_d)
		cube->input[KEY_A] = 0;
	if(keysym == XK_a)
		cube->input[KEY_D] = 0;
	if (keysym == XK_Right)
		cube->input[KEY_LEFT] = 0;
	if (keysym == XK_Left)
		cube->input[KEY_RIGHT] = 0;
	return (0);
}
