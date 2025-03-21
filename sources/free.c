/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:01:01 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/15 15:34:04 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdlib.h>

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map && *map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
}

static void	mlx_free(t_game *game)
{
	mlx_destroy_image(game->mlx, game->player);
	mlx_destroy_image(game->mlx, game->ground);
	mlx_destroy_image(game->mlx, game->coin);
	mlx_destroy_image(game->mlx, game->exit);
	mlx_destroy_image(game->mlx, game->wall);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game->map);
	free(game);
}

void	exit_game(t_game *game)
{
	mlx_free(game);
	exit(0);
}
