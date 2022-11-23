/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:33:19 by merlinbourg       #+#    #+#             */
/*   Updated: 2022/11/23 13:59:40 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	verif_around_map_bottom2(t_map_verif *map, char *line)
{
	int	i;

	i = ft_strlen_back(line);
	while (i-- != 0)
	{
		if (line[i] != '1')
			map->error++;
	}
	if (map->error != 0)
	{
		ft_putstr_fd("ERROR\nErreur de disposition de map.\n", 1);
		ft_get_out(line);
	}
}

void	verif_around_map_bottom(t_map_verif *map)
{
	char	*line;
	int		i;

	close(map->fd);
	map->fd = open(map->map_path, O_RDONLY);
	i = 0;
	while (i != map->map_y - 1)
	{
		line = get_next_line(map->fd);
		free(line);
		i++;
	}
	line = get_next_line(map->fd);
	verif_around_map_bottom2(map, line);
	free(line);
	map->error = 0;
	close(map->fd);
}
