/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:24 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/16 14:07:35 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../lib/libft/libft.h"
#include "../lib/printf/ft_printf.h"
#include "../so_long.h"

static int	count_coin(char **map)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static char	**copy_map(char **map)
{
	int		height;
	int		i;
	char	**copy;

	height = get_game_height(map);
	copy = malloc((height + 1) * sizeof(char *));
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map, int row, int col)
{
	if (map[row][col] == '1' || map[row][col] == 'F' || map[row][col] == 'E')
		return ;
	map[row][col] = 'F';
	flood_fill(map, row + 1, col);
	flood_fill(map, row - 1, col);
	flood_fill(map, row, col + 1);
	flood_fill(map, row, col - 1);
}

static int	check_exit_around(char **map)
{
	int	i;
	int	j;
	int	mapx;
	int	mapy;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				mapx = i;
				mapy = j;
			}
			j++;
		}
		i++;
	}
	if (map[mapx + 1][mapy] == 'F' || map[mapx - 1][mapy] == 'F'
		|| map[mapx][mapy + 1] == 'F' || map[mapx][mapy - 1] == 'F')
		return (0);
	return (-1);
}

int	is_map_solvable(t_game *game)
{
	char	**map_copy;

	map_copy = copy_map(game->map);
	flood_fill(map_copy, game->player_x, game->player_y);
	if (count_coin(map_copy) != 0 || check_exit_around(map_copy) != 0)
	{
		free_map(map_copy);
		ft_printf("ERROR\nMAP IS NOT SOLVABLE\n");
		return (0);
	}
	free_map(map_copy);
	return (1);
}
