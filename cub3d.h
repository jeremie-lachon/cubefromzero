#ifndef CUB3D_H

# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h> 
# include "utils/gnl/get_next_line.h"
# include <stdbool.h>
# include <math.h>
# include <float.h>

# define WIN_W 960
# define WIN_H 540
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define PI 3.14159265358979323846
# define CELL_SIZE 30
typedef struct s_img_data
{
    void    *img_ptr;
    char    *adress;

    int     bpp;
    int     size;
    int     endl;
    
    int     pix_w;
    int     pix_h;

}   t_img_data;

typedef struct s_data
{
    char    **map;

    int     pos_x;
    int     pos_y;
    
    int     map_w;
    int     map_h;
    char    facing;
}   t_data;

/*  
    X    Y
    (1, 0)      E
    (-1, 0)     W
    (0, 1)      N
    (0, -1)     S
*/
typedef struct s_ray
{
    float ray_angle;
    float distance;
    int flag;
} t_ray;

typedef struct s_player
{
    int     x;
    int     y;
    float   angle;
    float   dir_x;
    float   dir_y;
    float   plane_x;
    float   plane_y;
    float   fov_rad;
}   t_player;

typedef struct s_cube
{
    int     fd;
    char    **av; //utile ?
    void    *mlx_ptr;
    void    *win_ptr;
    bool    inputs[128];
    int     text_count;
    int     color_count;
    t_img_data  img;
    t_data      data;
    t_player    player;
    t_ray       ray;
}   t_cube;

#endif