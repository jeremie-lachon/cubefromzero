NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 
# CFLAGS += -MMD
# Path to mlx header files
MLX_INCLUDE = minilibx-linux/

# Path to utils directory
UTILS_DIR = utils/
#PRINTF_DIR = $(UTILS_DIR)printf/
GNL_DIR = -I$(UTILS_DIR)gnl/

# CFLAGS += $(MLX_INCLUDE) $(GNL_DIR)

SRC = test.c done.c raycasting.c

#DEP = $(SRC:.c=.d)
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
#	$(CC) $(CFLAGS) -I$(MLX_INCLUDE) -I$(PRINTF_DIR) -I$(GNL_DIR) -c $< -o $@

$(NAME): $(OBJ)
#	$(MAKE) -C $(PRINTF_DIR)
	$(MAKE) -C $(MLX_INCLUDE)
	$(CC) $(OBJ) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
# 	$(CC) $(OBJ) -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
#	$(CC) $(OBJ) $(PRINTF_DIR)libftprintf.a -L$(MLX_INCLUDE) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
#	$(CC) $(CFLAGS) $(OBJ) -lm -lz -o $(NAME)
#-include $(DEP)

all: $(NAME)

clean:
#	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJ) $(DEP)

fclean: clean
#	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

launch: re
	clear
	./$(NAME)

.PHONY: all clean fclean re launc