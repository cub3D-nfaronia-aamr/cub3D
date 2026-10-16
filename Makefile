# Program name
NAME = cub3d

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# get_next_line
GNL_DIR = src/get_next_line


GNL_SRC = $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c

# Sources
SRC =	src/main.c\
		src/utils.c\
		src/hook.c\
		src/parse/parser.c\
		src/parse/texture.c\
		$(GNL_SRC)

# Objects
OBJS = $(SRC:.c=.o)

# Test sources and objects
TEST_SRC = src/test.c \
		   src/draw_map.c \
		   src/hook.c \
		   src/utils.c
TEST_OBJS = $(TEST_SRC:.c=.o)
TEST_NAME = cub3d_test

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# MiniLibX (Linux)
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Includes
INC = -Ilibft -Iminilibx-linux -Iinclude -I$(GNL_DIR)

# Default rule
all: $(LIBFT) $(MLX) $(NAME)

# Build program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Build test program without the main program sources
test: $(TEST_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(TEST_NAME)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# MLX compilation
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Clean object files
clean:
	rm -f $(OBJS) $(TEST_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

# Recompile
re: fclean all

.PHONY: all test clean fclean re
