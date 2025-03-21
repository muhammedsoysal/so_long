/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:47:12 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/16 13:19:02 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../lib/printf/ft_printf.h"
#include <unistd.h>
#include <fcntl.h>

void	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->player = mlx_xpm_file_to_image(game->mlx, "textures/panda.xpm",
			&w, &h);
	game->ground = mlx_xpm_file_to_image(game->mlx, "textures/ground.xpm",
			&w, &h);
	game->coin = mlx_xpm_file_to_image(game->mlx, "textures/bambu.xpm",
			&w, &h);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit_locked.xpm",
			&w, &h);
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&w, &h);
}

void	draw_map(t_game *game, int x, int y)
{
	void	*img;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			img = NULL;
			if (game->map[y][x] == '1')
				img = game->wall;
			else if (game->map[y][x] == '0')
				img = game->ground;
			else if (game->map[y][x] == 'C')
				img = game->coin;
			else if (game->map[y][x] == 'E')
				img = game->exit;
			else if (game->map[y][x] == 'P')
				img = game->player;
			if (img)
				mlx_put_image_to_window(game->mlx, game->win, img,
					x * 32, y * 32);
		}
	}
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectible_count--;
		game->map[new_y][new_x] = '0';
	}
	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collectible_count == 0)
		{
			ft_printf("YOU WON THE GAME!\n");
			exit_game(game);
		}
		return ;
	}
	game->moves += 1;
	ft_printf("Moves: %d\n", game->moves);
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	draw_map(game, -1, -1);
}

void	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	texture_error(void)
{
	char	*arr[5];
	int		i;

	arr[0] = "textures/exit_locked.xpm";
	arr[1] = "textures/ground.xpm";
	arr[2] = "textures/panda.xpm";
	arr[3] = "textures/wall.xpm";
	arr[4] = "textures/bambu.xpm";
	i = 0;
	while (i < 5)
	{
		if (open(arr[i], O_RDONLY) == -1)
			return (ft_printf("ERROR\nTEXTURE NOT FOUND\n"), 0);
		i++;
	}
	return (1);
}
