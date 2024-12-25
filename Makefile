NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

# Path to mlx header files
MLX_INCLUDE = minilibx-linux/

# Path to utils directory
UTILS_DIR = utils/
#PRINTF_DIR = $(UTILS_DIR)printf/
GNL_DIR = $(UTILS_DIR)gnl/

SRC = test.c done.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_INCLUDE) -I$(GNL_DIR) -c $< -o $@
#	$(CC) $(CFLAGS) -I$(MLX_INCLUDE) -I$(PRINTF_DIR) -I$(GNL_DIR) -c $< -o $@

$(NAME): $(OBJ)
#	$(MAKE) -C $(PRINTF_DIR)
	$(MAKE) -C $(MLX_INCLUDE)
	$(CC) $(OBJ) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
#	$(CC) $(OBJ) $(PRINTF_DIR)libftprintf.a -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re