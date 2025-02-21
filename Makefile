NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fPIE
# CFLAGS += -MMD
# Path to mlx header files
INC = -Iincludes -Iutils/gnl -Iminilibx-linux/
MLX_INCLUDE = minilibx-linux/


# Path to utils directory
UTILS_DIR = utils/
#PRINTF_DIR = $(UTILS_DIR)printf/
GNL_DIR = -I$(UTILS_DIR)gnl/

# CFLAGS += $(MLX_INCLUDE) $(GNL_DIR)

SRC_GNL = get_next_line.c get_next_line_utils.c

SRC_PARSE = o.c  raycasting.c  main.c

SRC_LIB = ft_strlen.c ft_split.c list_tools.c frees.c angle_tools.c misc.c ft_strtrim.c ft_calloc.c ft_atoi.c

SRC_PARSING = check_map.c init.c

SRC_EXEC = draw.c find_x_ray.c find_y_ray.c display.c movement.c raycast_checks.c keys.c
SRC = main.c done.c raycasting.c
# SRC = essai.c

DIR_GNL = utils/gnl/
DIR_EXEC = exec/
DIR_LIB = lib/
DIR_PARSING = parsing/

#DEP = $(SRC:.c=.d)
OBJ_E = $(addprefix $(DIR_EXEC), $(SRC_EXEC:.c=.o))
OBJ_G = $(addprefix $(DIR_GNL), $(SRC_GNL:.c=.o))
OBJ_L = $(addprefix $(DIR_LIB), $(SRC_LIB:.c=.o))
OBJ_PARSING = $(addprefix $(DIR_PARSING), $(SRC_PARSING:.c=.o))

OBJ_P = $(SRC_PARSE:.c=.o)
OBJ = $(SRC:.c=.o)

OBJ_ALLPARSE = $(OBJ_G) $(OBJ_L) $(OBJ_P) $(OBJ_E) $(OBJ_PARSING)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
#	$(CC) $(CFLAGS) -I$(MLX_INCLUDE) -I$(PRINTF_DIR) -I$(GNL_DIR) -c $< -o $@

$(NAME): $(OBJ)
#	$(MAKE) -C $(PRINTF_DIR)
	$(MAKE) -C $(MLX_INCLUDE)
	$(CC) $(OBJ) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -fPIE -pie -o $(NAME)
# 	$(CC) $(OBJ) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
#	$(CC) $(OBJ) $(PRINTF_DIR)libftprintf.a -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
#	$(CC) $(CFLAGS) $(OBJ) -lm -lz -o $(NAME)
#-include $(DEP)

parse: $(OBJ_ALLPARSE)
	$(MAKE) -C $(MLX_INCLUDE)
	$(CC) $(OBJ_ALLPARSE) $(INC) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -fPIE -pie -o parse

all: $(NAME)

clean:
#	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJ) $(DEP) $(OBJ_ALLPARSE)

fclean: clean
#	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

gdb: fclean parse
	gdb --command=gdbcmds --args ./parse test.cub

launch: re
	clear
	./$(NAME)

.PHONY: all clean fclean re launc