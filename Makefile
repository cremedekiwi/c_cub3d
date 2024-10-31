NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -w -g3
LINK = -lm -lX11 -lXext
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a
MLX_PATH = minilibx-linux/
MLX = $(MLX_PATH)libmlx.a

INCLUDES = -I./includes -I$(LIB_PATH) -I$(MLX_PATH)

SRC_PATH = sources/
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
SRCS = $(addprefix $(SRC_PATH), $(SRC_FILES))

OBJ_PATH = obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJECTS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all : $(NAME)

$(NAME) : $(MLX) $(OBJECTS) $(LIBFT)
	@echo "${NAME}"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX) $(LIBFT) $(LINK) -o $@

$(MLX) :
	@echo "mlx"
	@make -C $(MLX_PATH) >/dev/null 2>&1 --no-print-directory

$(LIBFT) :
	@echo "libft"
	@make -C $(LIBFT_PATH) --no-print-directory

$(OBJ_PATH)%.o : $(SRC_PATH)%.c | $(OBJ_PATH)
	@echo "compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH) :
	@mkdir -p $(OBJ_PATH)

bonus : all

clean :
	@echo "clean"
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH) --no-print-directory
	@make clean -C $(MLX_PATH) >/dev/null 2>&1 --no-print-directory

fclean: clean
	@echo "fclean"
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re : fclean all

.PHONY : all re clean fclean

debug :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --leak-resolution=high ./${NAME}
