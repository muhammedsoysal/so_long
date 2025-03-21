/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:34:56 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/15 15:31:49 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "../lib/printf/ft_printf.h"
#include "../so_long.h"

int	get_game_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

int	is_map_enclosed(char **map)
{
	int	height;
	int	row;
	int	col;

	height = get_game_height(map);
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (row == 0 || row == height - 1 || col == 0
				|| col == (int)ft_strlen(map[row]) - 1)
			{
				if (map[row][col] != '1')
					return (ft_printf("ERROR\nMAP IS NOT ENCLOSED\n"), 0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	has_valid_characters(char **map)
{
	int	row;
	int	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] != '1' && map[row][col] != '0'
				&& map[row][col] != 'P'
				&& map[row][col] != 'E' && map[row][col] != 'C')
			{
				ft_printf("ERROR\nINVALID CHARACTER IN MAP\n");
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

static void	count_elements(t_game *game, int row, int col)
{
	if (game->map[row][col] == 'P')
	{
		game->player_x = row;
		game->player_y = col;
		game->player_count++;
	}
	else if (game->map[row][col] == 'E')
		game->exit_count++;
	else if (game->map[row][col] == 'C')
		game->collectible_count++;
}

int	has_required_elements(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	game->player_count = 0;
	game->exit_count = 0;
	game->collectible_count = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			count_elements(game, row, col);
			col++;
		}
		row++;
	}
	if (game->player_count != 1 || game->exit_count != 1
		|| game->collectible_count == 0)
		return (ft_printf("ERROR\nINVALID NUMBER OF ELEMENTS\n"), 0);
	return (1);
}
