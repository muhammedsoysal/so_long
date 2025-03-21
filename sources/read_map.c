/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:09 by musoysal          #+#    #+#             */
/*   Updated: 2025/03/17 16:10:42 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "../lib/gnl/get_next_line.h"
#include "../lib/printf/ft_printf.h"
#include <fcntl.h>

static int	is_only_spaces(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

static void	handle_error(char *msg, char *holder_map, int fd)
{
	free(holder_map);
	close(fd);
	ft_printf("ERROR\n%s\n", msg);
}

static char	*read_map_lines(int fd, char *holder_map)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[1] != '\0' && line[0] != '\0')
		{
			temp = holder_map;
			holder_map = ft_strjoin(temp, line);
			free(temp);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (holder_map);
}

char	**read_map(char *file_name)
{
	int		fd;
	char	*holder_map;
	char	**map;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_printf("ERROR\nFAILED TO OPEN FILE\n"), NULL);
	holder_map = get_next_line(fd);
	if (holder_map == NULL || is_only_spaces(holder_map)
		|| holder_map[0] == '\0')
	{
		handle_error("MAP IS EMPTY", holder_map, fd);
		return (NULL);
	}
	holder_map = read_map_lines(fd, holder_map);
	if (holder_map[ft_strlen(holder_map) - 1] == '\n')
	{
		handle_error("MAP CANNOT END WITH A NEWLINE", holder_map, fd);
		return (NULL);
	}
	close(fd);
	map = ft_split(holder_map, '\n');
	free(holder_map);
	return (map);
}
