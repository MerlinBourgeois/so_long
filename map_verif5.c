/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:30:24 by merlinbourg       #+#    #+#             */
/*   Updated: 2022/11/23 13:59:03 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen_back(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != 0)
		i++;
	return (i);
}

void	ft_get_out(char *line)
{
	free(line);
	exit (EXIT_FAILURE);
}

void	verif_around_map_top(t_map_verif *map)
{
	char	*line;
	int		i;

	line = get_next_line(map->fd);
	i = ft_strlen_back(line);
	map->map_x = i;
	i--;
	while (i != 0)
	{
		if (line[i] != '1')
			map->error++;
		i--;
	}
	if (map->error != 0)
	{
		ft_putstr_fd("ERROR\nErreur de disposition de map.\n", 1);
		ft_get_out(line);
	}
	map->error = 0;
	free(line);
}

void	verif_around_map_middle2(t_map_verif *map, char *line)
{
	if (map->error != 0)
	{
		ft_putstr_fd("ERROR\nErreur de disposition de map.\n", 1);
		ft_get_out(line);
	}
	map->error = 0;
	close(map->fd);
}

void	verif_around_map_middle(t_map_verif *map)
{
	char	*line;
	int		i;

	line = get_next_line(map->fd);
	map->map_y = 0;
	map->map_y++;
	while (line != NULL)
	{
		i = map->map_x - 1;
		while (i != 0)
		{
			if (line[0] != '1' || line[map->map_x - 1] != '1')
				map->error++;
			i--;
		}
		if (ft_strlen_back(line) != (size_t)map->map_x)
			map->error++;
		free(line);
		line = get_next_line(map->fd);
		map->map_y++;
	}
	verif_around_map_middle2(map, line);
	free(line);
}
