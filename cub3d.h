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
// # include "utils/gnl/get_next_line.h"
# include <stdbool.h>
# include <math.h>
# include <float.h>
#include <sys/time.h>
# define MAX_VIEW_DISTANCE 50
# define WIN_W 1200
# define WIN_H 800
# define FOV_W 90.F
# define FOV_H 100.F
# define ROTATION_SPEED .006
# define PLAYER_SPEED 40
# define PI 3.14159265358979F
# define CELL_SIZE 1
# define EPSILON 1e-6
# define LARGE_NUMBER 1e6
# define FOV_DEGREE (FOV_W / 360.F)
# define HALF_WIDTH (WIN_W / 2)
# define ADJACENT (HALF_WIDTH / tanf(FOV_DEGREE * PI))
# define MAP_W 190
# define MAP_H 90

enum texture
{
    FROID1,
    FROID2,
    FROID3,
    FROID4,
    NORTH,
    SOUTH,
    EAST,
    WEST,

};

enum move
{
    KEY_W,
    KEY_S,
    KEY_A,
    KEY_D,
    KEY_LEFT,
    KEY_RIGHT,
    MOUSE_LEFT,
    MOUSE_RIGHT
};
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
    unsigned int FC[2];
}   t_data;

typedef struct s_ray
{
    int index;
    float tetta;
    float distance;
    int flag;
    double h_x;
    double h_y;
    double v_x;
    double v_y;
} t_ray;

typedef struct s_player
{
    float     x;
    float     y;
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
    void    *mlx_ptr;
    void    *win_ptr;
    bool    input[8];
    int     NSWE;
    t_img_data  img;
    t_data      data;
    t_player    player;
    t_ray       ray;
    int         mouse_x;
    int         mouse_y;
	t_img_data	image1;
	t_img_data	image2;
	t_img_data	minimap;
    t_img_data     texture[9];
    int minimap_w;
    int minimap_h;
    struct timeval time;
    int frame;
}   t_cube;


int map_filler(t_data *data);
int	escape(t_cube *cube);
int key_press(int keysym, t_cube *cube);
int init_mlx(t_cube *cube);
void raycasting(t_cube *cube);
void	move_player(t_cube *cube, float angle);
float	fix_angle(float angle);
void moving (t_cube *cube);
int key_release(int keysym, t_cube *cube);
void display_pix(t_img_data *img, int x, int y, int color);
void ft_putpixel(int ray, int i, t_cube *cube, int color);
#endif