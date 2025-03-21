/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:34:25 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/17 16:19:59 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "lib/printf/ft_printf.h"
#include "lib/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>

static int	dest_win(t_game *game)
{
	exit_game(game);
	return (0);
}

static int	key_handle(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	else if (keycode == 119)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == 115)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == 97)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == 100)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}

static void	get_game_size(t_game *game, int *width, int *height)
{
	*width = 0;
	*height = 0;
	while (game->map[*height])
	{
		if ((int)ft_strlen(game->map[*height]) > *width)
			*width = (int)ft_strlen(game->map[*height]);
		(*height)++;
	}
	game->moves = 0;
}

static int	arg_check(int argc, char *argv[])
{
	int		len;
	char	*path;

	if (argc != 2)
	{
		ft_printf("ERROR\nWRONG NUMBER OF ARGUMENTS\n");
		return (0);
	}
	path = argv[1];
	len = 0;
	while (path[len] != '\0')
		len++;
	if (path[len - 1] != 'r' || path[len - 2] != 'e'
		|| path[len - 3] != 'b' || path[len - 4] != '.')
	{
		ft_printf("ERROR\nWRONG FILE EXTENSION\n");
		return (0);
	}
	if (open(path, O_RDONLY) == -1)
	{
		return (ft_printf("ERROR\nFILE NOT FOUND\n"), 0);
	}
	if (texture_error() == 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	int		width;
	int		height;

	if (!arg_check(argc, argv))
		return (1);
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (ft_printf("ERROR\nMEMORY ALLOCATION FAILED\n"), 1);
	game->map = read_map(argv[1]);
	if (game->map == NULL)
		return (free(game->map), free(game), 1);
	if (validate_map(game) != 1)
		return (free_map(game->map), free(game), 1);
	get_game_size(game, &width, &height);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, width * 32, height * 32, "game");
	load_textures(game);
	find_player(game);
	draw_map(game, -1, -1);
	mlx_key_hook(game->win, key_handle, game);
	mlx_hook(game->win, 17, 0L, dest_win, game);
	mlx_loop(game->mlx);
	return (0);
}
