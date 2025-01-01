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
# define MAX_VIEW_DISTANCE 50
# define WIN_W 1200
# define WIN_H 800
# define FOV 60
# define ROTATION_SPEED .006
# define PLAYER_SPEED 40
# define PI 3.1415926535897932384
# define CELL_SIZE 60
# define EPSILON 1e-6
# define LARGE_NUMBER 1e6

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
    int index;
    float ray_angle;
    float distance;
    int flag;
    double h_x;
    double h_y;
    double v_x;
    double v_y;
} t_ray;

typedef struct s_player
{
    double     x;
    double     y;
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
    t_img_data     texture[5];
}   t_cube;


int map_filler(t_data *data);
int	escape(t_cube *cube);
int key_press(int keysym, t_cube *cube);
int init_mlx(t_cube *cube);


#endif