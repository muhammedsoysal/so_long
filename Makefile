NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX = minilibx-linux
MLX_FLAGS = -L$(MLX) -lmlx -lXext -lX11 -lm -lz

PRINTF_DIR = lib/printf
GNL_DIR = lib/gnl
LIBFT_DIR = lib/libft

SRCS = so_long.c\
		sources/map_check.c\
		sources/map_check2.c\
		sources/flood_fill.c\
		sources/free.c\
		sources/read_map.c\
		sources/utils.c\
		$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(MAKE) -s -C $(MLX)
	@$(MAKE) -s -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s -C $(PRINTF_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(PRINTF_DIR) fclean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MLX) clean

re: fclean all

.PHONY: all clean fclean re
