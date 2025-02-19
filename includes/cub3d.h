#ifndef CUB3D_H

# define CUB3D_H

# include "mlx.h"
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
# include "get_next_line.h"
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

// enum texture
// {
//     FROID1,
//     FROID2,
//     FROID3,
//     FROID4,
//     NORTH,
//     SOUTH,
//     EAST,
//     WEST,

// };

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
	int		pix_h;
}   t_img_data;

typedef struct s_data
{
	int		**map;

	// int     pos_x;
	// int     pos_y;
	int     map_w;
	int     map_h;
	// char    facing;
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
	int	hitx;
	int	hity;
	int	hit;
	unsigned int *adress;
	t_img_data  *texture;
} t_ray;

// typedef struct s_player
// {
//     float     x;
//     float     y;
//     float   angle;
//     float   dir_x;
//     float   dir_y;
//     float   plane_x;
//     float   plane_y;
//     float   fov_rad;
// }   t_player;

enum
{
	PLAYER_X,
	PLAYER_Y,
	ANGLE,
	PLAYER_COUNT
};

enum
{
	SPACE,
	WALL,
	OUT,
	DOOR,
	SPRITE
};

enum
{
	NO,
	WE,
	SO,
	EA,
	DO,
	SP
};

typedef struct s_list
{
	struct s_list *next;
	void *data;
}	t_list;

typedef struct s_parse
{
	char	**textures;
	int		F;
	int		C;
	float	player[4];
	int		**map;
	int		width;
	int		height;
}	t_parse;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img_data	*img1;
	t_img_data	*img2;
	t_img_data	*image;
}	t_mlx;

typedef struct s_cube
{
	bool    	input[8];
	int     	mouse_x;
	int			mouse_y;
	int 		frame;
	int     	NSWE;
	t_ray		ray;
	t_data		data;
	int			minimap_w;
	int			minimap_h;
	float		player[3];
	t_img_data	*texture[5];
	int			nsprite;
	t_img_data	**sprite;
	t_mlx		*mlx;
}	t_cube;

// typedef struct s_cube
// {
//     int     fd;
//     void    *mlx_ptr;
//     void    *win_ptr;
//     bool    input[8];
//     int     NSWE;
//     t_img_data  img;
//     t_data      data;
//     t_player    player;
//     t_ray       ray;
//     int         mouse_x;
//     int         mouse_y;
// 	t_img_data	image1;
// 	t_img_data	image2;
// 	t_img_data	minimap;
//     t_img_data     texture[9];
//     int minimap_w;
//     int minimap_h;
//     struct timeval time;
//     int frame;
// }   t_cube;


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
void ft_putpixel(int ray, int i, t_cube *cube, int color, int flag);
void	*ft_calloc(size_t nmemb, size_t size);

// Structs


// LIBS & MISC

char	**ft_split(char const *s, char c);
char	**ft_freesplit(char **res, int n);
size_t	ft_strlen(const char *str);

// Frees
int intfree(int **array, int i);
int parsefree(t_parse *parse);
int free_cube(t_cube *cube);
int ft_clear_display(t_mlx *mlx);

// List tools
int listfree(t_list *list);
int listaddfront(t_list **list, t_list *new);
t_list *listnew(void *data);
int listsize(t_list *list);
int maxsize(t_list *list);

//Draw
void display_pix(t_img_data *img, int x, int y, int color);
void ft_putpixel(int ray, int i, t_cube *cube, int color, int flag);
void draw_wall(float top_pixel, t_cube *cube, float offset);

float	find_x_ray(t_cube *cube, float angle, float fixed_angle);
float	find_y_ray(t_cube *cube, float angle, float fixed_angle);
int check_wall(float y, float x, t_cube *cube);
#endif