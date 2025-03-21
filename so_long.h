/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:30:30 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/16 16:14:27 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*player;
	void	*wall;
	void	*coin;
	void	*exit;
	void	*ground;
	char	**map;
	int		player_count;
	int		exit_count;
	int		collectible_count;
	int		player_x;
	int		player_y;
	int		moves;
}	t_game;

int		validate_map(t_game *game);
void	free_map(char **map);
char	**read_map(char *file_name);
int		is_map_enclosed(char **map);
int		has_valid_characters(char **map);
int		is_map_solvable(t_game *game);
int		get_game_height(char **map);
int		has_required_elements(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	load_textures(t_game *game);
void	draw_map(t_game *game, int x, int y);
void	find_player(t_game *game);
void	exit_game(t_game *game);
int		texture_error(void);
#endif
