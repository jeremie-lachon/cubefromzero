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
# include <sys/time.h>
# define MAX_VIEW_DISTANCE 50
# define WIN_W 1600
# define WIN_H 900
# define FOV_W 90.F
# define FOV_H 100.F
# define ROTATION_SPEED .006
# define PLAYER_SPEED 40
# define PI 3.14159265358979F
# define CELL_SIZE 1
# define EPSILON 1e-6
# define LARGE_NUMBER 1e6
# define MAP_W 190
# define MAP_H 90
# define MM_SIZE 25

enum e_move
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
	void	*img_ptr;
	char	*adress;
	int		bpp;
	int		size;
	int		endl;
	int		pix_w;
	int		pix_h;
}	t_img_data;

typedef struct s_data
{
	int				**map;
	int				map_w;
	int				map_h;
	unsigned int	fc[2];
}	t_data;

typedef struct s_ray
{
	int				index;
	float			tetta;
	float			distance;
	int				flag;
	double			h_x;
	double			h_y;
	double			v_x;
	double			v_y;
	int				hitx;
	int				hity;
	int				hit;
	unsigned int	*adress;
	t_img_data		*texture;
}	t_ray;

enum	e_values
{
	PLAYER_X,
	PLAYER_Y,
	ANGLE,
	PLAYER_COUNT
};

enum	e_sprite
{
	SPACE,
	WALL,
	OUT,
	DOOR,
	SPRITE
};

enum e_side
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
	struct s_list	*next;
	void			*data;
}	t_list;

typedef struct s_parse
{
	char	**textures;
	int		f;
	int		c;
	float	player[4];
	int		**map;
	int		width;
	int		height;
}	t_parse;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img_data	*img1;
	t_img_data	*img2;
	t_img_data	*image;
}	t_mlx;

typedef struct s_cube
{
	bool		input[8];
	int			mouse_x;
	int			mouse_y;
	int			frame;
	int			nswe;
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

char	*cb_strdup(const char *s1);
int		cb_strncmp(const char *s1, const char *s2, size_t n);
char	**cb_split(char const *s, char c);
char	**cb_freesplit(char **res, int n);
char	*custom_read(int fd, int check);
char	*cb_strchr(const char *s, int c);
char	*cb_substr(char const *s, int start, int len);
char	*cb_strtrim(char *s1, char *set);
void	printmap(t_parse *parse);
void	*cb_calloc(size_t nmemb, size_t size);
void	mouse_rotation(t_cube *cube);
void	moving(t_cube *cube);
float	added_angle(t_cube *cube);
float	fix_angle(float angle);
size_t	cb_strlen(const char *str);
t_parse	*parseinit(void);
t_cube	*parse_to_cube(t_parse *parse, t_mlx *mlx);
t_list	*listnew(void *data);
void	freetexts(t_cube *cube);
void	display_pix(t_img_data *img, int x, int y, int color);
void	cb_putpixel(int i, t_cube *cube, int color, int flag);
void	draw_wall(float top_pixel, t_cube *cube, float offset);
void	draw_wall_other(t_cube *cube, float pixel, float offset, int i);
void	draw_other(float top, t_cube *cube);
void	wall_display(t_cube *cube, float dist, float offset);
void	minimap_display(t_cube *cube);
float	find_x_ray(t_cube *cube, float angle, float fixed_angle);
float	find_y_ray(t_cube *cube, float angle, float fixed_angle);

void	raycasting(t_cube *cube);
void	wall_check(float distxy[2], t_cube *cube, float angle, float cosangled);
int		cb_atoi(const char *nptr);
int		key_release(int keysym, t_cube *cube);
int		key_press(int keysym, t_cube *cube);
int		escape(t_cube *cube);
int		parse_filler2(char *buf, t_parse *cube);
int		sett(char *str);
int		skip(char *s, int *i, int check);
int		fillsprite(t_parse *parse, t_cube *cube, t_mlx *mlx);
int		checkmap(t_parse *parse);
int		listsize(t_list *list);
int		maxsize(t_list *list);
int		listfree(t_list *list);
int		listaddfront(t_list **list, t_list *new);
int		intfree(int ***array, int i);
int		parsefree(t_parse *parse);
int		free_cube(t_cube *cube);
int		cb_clear_display(t_mlx *mlx);
int		cb_mlx_start(t_mlx **mlx_address);
int		mapper(int fd, t_parse *parse, char *str);
int		imgstruct(t_cube *cube, int num, t_mlx *mlx, t_parse *parse);
int		parse_filler(int fd, t_parse *cube);
int		check_wall(float y, float x, t_cube *cube);
int		check_door(int x, int y, t_cube *cube);
int		check_wall(float y, float x, t_cube *cube);
#endif