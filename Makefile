NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -w -g3
LINK = -lm -lX11 -lXext
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a
MLX_PATH = minilibx-linux/
MLX = $(MLX_PATH)libmlx.a

INCLUDES = -I./includes -I$(LIBFT_PATH) -I$(MLX_PATH)

SRC_PATH = sources/mandatory/
BONUS_PATH = sources/bonus/
OBJ_PATH = obj/

SRC_FILES = main.c \
			input.c \
			render.c \
			movement.c \
			maths_utils.c \
			draw.c \
			texture.c \
			wall.c \
			tab.c \
			exit.c \
			parse.c \
			map.c \
			raycasting.c

BONUS_FILES = main_bonus.c \
			input_bonus.c \
			render_bonus.c \
			movement_bonus.c \
			maths_utils_bonus.c \
			draw_bonus.c \
			texture_bonus.c \
			wall_bonus.c \
			tab_bonus.c \
			exit_bonus.c \
			parse_bonus.c \
			map_bonus.c \
			raycasting_bonus.c \
			torch_bonus.c

SRCS = $(addprefix $(SRC_PATH), $(SRC_FILES))
BONUS_SRCS = $(addprefix $(BONUS_PATH), $(BONUS_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_FILES:.c=.o)
OBJECTS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
BONUS_OBJECTS = $(addprefix $(OBJ_PATH), $(BONUS_OBJ_FILES))

all: $(NAME)

$(NAME): $(MLX) $(OBJECTS) $(LIBFT)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX) $(LIBFT) $(LINK) -o $@

$(BONUS_NAME): $(MLX) $(BONUS_OBJECTS) $(LIBFT)
	@echo "Building $(BONUS_NAME) with bonus"
	@$(CC) $(CFLAGS) $(BONUS_OBJECTS) $(MLX) $(LIBFT) $(LINK) -o $@

bonus: $(BONUS_NAME)

$(MLX):
	@echo "Building mlx library"
	@make -C $(MLX_PATH) >/dev/null 2>&1 --no-print-directory

$(LIBFT):
	@echo "Building libft library"
	@make -C $(LIBFT_PATH) --no-print-directory

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH)%.o: $(BONUS_PATH)%.c | $(OBJ_PATH)
	@echo "Compiling bonus $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@echo "Cleaning object files"
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH) --no-print-directory
	@make clean -C $(MLX_PATH) >/dev/null 2>&1 --no-print-directory

fclean: clean
	@echo "Removing executable and libraries"
	@rm -rf $(NAME) $(BONUS_NAME)  # Remove both executables
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re: fclean all

debug:
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-resolution=high ./${NAME}

.PHONY: all re clean fclean debug bonus
