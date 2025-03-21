/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:30:17 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/16 14:22:54 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/printf/ft_printf.h"
#include "../lib/libft/libft.h"
#include "../so_long.h"

static int	is_map_rectangular(char **map)
{
	int	expected_width;
	int	row;

	row = 0;
	expected_width = (int)ft_strlen(map[0]);
	while (map[row])
	{
		if ((int)ft_strlen(map[row]) != expected_width)
		{
			ft_printf("ERROR\nMAP IS NOT RECTANGULAR\n");
			return (0);
		}
		row++;
	}
	return (1);
}

static int	is_collectible_blocked(char **map, int row, int col)
{
	return ((map[row - 1][col] == '1' || map[row - 1][col] == 'E') &&
			(map[row + 1][col] == '1' || map[row + 1][col] == 'E') &&
			(map[row][col - 1] == '1' || map[row][col - 1] == 'E') &&
			(map[row][col + 1] == '1' || map[row][col + 1] == 'E'));
}

static int	has_blocked_collectible(char **map)
{
	int	row;
	int	col;

	row = 1;
	while (map[row + 1])
	{
		col = 1;
		while (map[row][col + 1])
		{
			if (map[row][col] == 'C' && is_collectible_blocked(map, row, col))
			{
				ft_printf("ERROR\nCOLLECTIBLE IS BLOCKED\n");
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	is_player_blocked(char **map, int row, int col)
{
	if ((map[row - 1][col] == '1' || map[row - 1][col] == 'E')
		&& (map[row + 1][col] == '1' || map[row + 1][col] == 'E')
		&& (map[row][col - 1] == '1' || map[row][col - 1] == 'E')
		&& (map[row][col + 1] == '1' || map[row][col + 1] == 'E'))
	{
		ft_printf("ERROR\nPLAYER IS BLOCKED\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	return (is_map_rectangular(game->map)
		&& is_map_enclosed(game->map)
		&& has_required_elements(game)
		&& has_valid_characters(game->map)
		&& is_player_blocked(game->map, game->player_x, game->player_y)
		&& has_blocked_collectible(game->map)
		&& is_map_solvable(game));
}
