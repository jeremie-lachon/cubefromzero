#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "cub3d.h"

typedef struct oo
{
    void *ptr;
    void *win;
} t_o;
int main(void)
{
    // t_cube *cube;
    t_o *o;
    o = malloc(sizeof(t_o));
    // cube = calloc(1 , sizeof(t_cube));
    // cube = (t_cube){0};
    o->ptr = mlx_init();
    // printf("Size %ld\n", sizeof(o->ptr));
    printf("HEHE\n");
       o->win = mlx_new_window(o->ptr, WIN_W, WIN_H, "Cub3d");
    exit(1);
}