NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fPIE
CFLAGS += -MMD
# Path to mlx header files
INC = -Iincludes -Iutils/gnl -Iminilibx-linux/
MLX_INCLUDE = minilibx-linux/


# Path to utils directory
UTILS_DIR = utils/
#PRINTF_DIR = $(UTILS_DIR)printf/
GNL_DIR = -I$(UTILS_DIR)gnl/

# CFLAGS += $(MLX_INCLUDE) $(GNL_DIR)

SRC_GNL = get_next_line.c get_next_line_utils.c

SRC_PARSE = main.c

SRC_LIB = ft_strlen.c ft_split.c list_tools.c frees.c angle_tools.c misc.c ft_strtrim.c ft_calloc.c ft_atoi.c ft_strncmp.c ft_strdup.c

SRC_PARSING = check_map.c  filler.c  init.c map_tools.c \
				mlx_starter.c  parse_to_cube.c \
				misc.c parse_init.c

SRC_EXEC = draw.c find_x_ray.c find_y_ray.c display.c movement.c raycast_checks.c keys.c minimap.c raycasting.c
SRC = main.c
# SRC = essai.c

DIR_GNL = utils/gnl/
DIR_EXEC = exec/
DIR_LIB = lib/
DIR_PARSING = parsing/


OBJ_E = $(addprefix $(DIR_EXEC), $(SRC_EXEC:.c=.o))
OBJ_G = $(addprefix $(DIR_GNL), $(SRC_GNL:.c=.o))
OBJ_L = $(addprefix $(DIR_LIB), $(SRC_LIB:.c=.o))
OBJ_PARSING = $(addprefix $(DIR_PARSING), $(SRC_PARSING:.c=.o))
OBJ_P = $(SRC_PARSE:.c=.o)
OBJ = $(SRC:.c=.o)

OBJ_ALLPARSE = $(OBJ_G) $(OBJ_L) $(OBJ_P) $(OBJ_E) $(OBJ_PARSING)
DEP = $(OBJ_ALLPARSE:.o=.d)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_ALLPARSE)
	$(MAKE) -C $(MLX_INCLUDE)
	$(CC) $(OBJ_ALLPARSE) $(INC) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -fPIE -pie -o $(NAME)
-include $(DEP)


clean:
	rm -f $(OBJ) $(DEP) $(OBJ_ALLPARSE)

fclean: clean
	$(MAKE) -C $(MLX_INCLUDE) clean
	rm -f $(NAME) parse $(DEP)

re: fclean all

gdb: fclean all
	gdb --command=gdbcmds $(NAME)

launch: re
	clear
	./$(NAME)

.PHONY: all clean fclean re launch gdb 