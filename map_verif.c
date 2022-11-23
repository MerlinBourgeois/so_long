/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:33:57 by mebourge          #+#    #+#             */
/*   Updated: 2022/11/23 18:45:38 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	verif_around_map_p_e2(t_map_verif *map, char *line)
{
	if (map->player != 1 || map->out != 1 || map->nb_colectible == 0)
	{
		ft_putstr_fd("ERROR\nDisposition de joueur de sortie", 1);
		ft_putstr_fd(" ou de collectible.\n", 1);
		ft_get_out(line);
	}
	map->error = 0;
	close(map->fd);
}

void	verif_around_map_p_e(t_map_verif *map)
{
	char	*line;
	int		i;

	map->fd = open(map->map_path, O_RDONLY);
	line = get_next_line(map->fd);
	map->map_y++;
	map->map_mapleng = 0;
	while (line != NULL)
	{
		i = map->map_x - 1;
		while (i != 0)
		{
			if (line[i] == 'P')
				map->player++;
			if (line[i] == 'E')
				map->out++;
			if (line[i] == 'C')
				map->nb_colectible++;
			i--;
		}
		free(line);
		line = get_next_line(map->fd);
		map->map_y++;
		map->map_mapleng++;
	}
	verif_around_map_p_e2(map, line);
	free(line);
}

void	verif_map_path(t_map_verif *map)
{
	int		i;
	int		j;
	char	*ber;

	i = ft_strlen(map->map_path);
	j = 0;
	ber = ".ber";
	i = i - 4;
	while ((size_t)i != ft_strlen(map->map_path))
	{
		if (map->map_path[i] != ber[j])
			map->error++;
		i++;
		j++;
	}
	if (map->error != 0)
	{
		ft_putstr_fd("ERROR\nErreur d'extention de carte.\n", 1);
		exit(EXIT_FAILURE);
	}
	map->error = 0;
}

void	verif_around_map(t_map_verif *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (line == NULL || line[0] == '\n')
	{
		ft_putstr_fd("ERROR\nLa carte est vide ou débute par un \\n.\n", 1);
		exit (EXIT_FAILURE);
	}
	free(line);
	close(map->fd);
	map->fd = open(map->map_path, O_RDONLY);
	verif_map_path(map);
	verif_around_map_top(map);
	verif_around_map_middle(map);
	verif_around_map_bottom(map);
	verif_around_map_p_e(map);
	ft_path_finding(map);
}

int	ft_init_verif(char *path)
{
	t_map_verif	*map;

	map = malloc(sizeof(t_map_verif));
	if (!map)
		return (1);
	map->map_path = path;
	map->fd = open(map->map_path, O_RDONLY);
	verif_around_map(map);
	free(map);
	return (0);
}
