/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:00:16 by merlinbourg       #+#    #+#             */
/*   Updated: 2022/11/23 17:48:35 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_list(t_map_corr *chain)
{
	t_map_corr	*e;
	t_map_corr	*last;

	if (!chain)
		return ;
	while (chain->next != NULL)
	{
		e = chain;
		last = get_last(chain);
		while (e->next != last)
			e = e->next;
		free(e->next);
		e->next = NULL;
	}
}

t_map_corr	*ft_path_red3(t_map_verif *map, t_map_corr *chain)
{
	t_map_corr	*e;
	t_map_corr	*co;

	map->lower_cost = 2147483647;
	co = malloc(sizeof(t_map_corr));
	if (!co)
		return (NULL);
	co->next = NULL;
	e = get_last(chain);
	map->x = e->x;
	map->y = e->y;
	return (co);
}

void	ft_path_finding_map_update(t_map_verif *map, t_map_corr *chain)
{
	t_map_corr	*co;

	while (map->map_compl[map->y][map->x] != 'E')
	{
		co = ft_path_red3(map, chain);
		if (ft_path_finding_map_search_neighbour(map) == 0)
		{
			ft_putstr_fd("ERROR\nPas de chemin pour acceder a la sortie.\n", 1);
			exit (EXIT_FAILURE);
		}
		ft_path_red(map, chain, co);
		ft_path_red2(map, chain, co);
		if (map->lower_cost == 0)
			break ;
		else if (map->lower_cost == 2147483647)
		{
			chain = ft_path_finding_map_suppup(map, chain);
			free(co);
		}
		else
			chain = lstadd_back(chain, co);
	}
	free(co);
	ft_free_list(chain);
}

void	ft_path_finding2(t_map_verif *map, char **map_path, t_map_corr co)
{
	int	i;

	i = 0;
	map->map_compl = map_path;
	ft_path_finding_map_locate(map, 'E');
	map->out_x = map->x;
	map->out_y = map->y;
	map->x = 0;
	map->y = 0;
	ft_path_finding_map_manathan(map);
	ft_path_finding_map_put_tab(map);
	ft_path_finding_map_locate(map, 'P');
	co.x = map->x;
	co.y = map->y;
	ft_path_finding_map_update(map, &co);
	while (i != map->map_y && map->map_compl[i])
		free(map->map_compl[i++]);
	free(map->map_compl);
	i = 0;
	while (i != map->map_mapleng && map->map_dist[i])
		free(map->map_dist[i++]);
	free(map->map_dist);
	ft_free_list(&co);
}

void	ft_path_finding(t_map_verif *map)
{
	char		*line;
	char		**map_path;
	int			i;
	t_map_corr	co;

	co.next = NULL;
	map->fd = open(map->map_path, O_RDONLY);
	if (read(map->fd, 0, 0) < 0)
		return ;
	map_path = malloc(map->map_y * sizeof(char *));
	if (!map_path)
		return ;
	i = 0;
	while (i != map->map_y)
	{
		line = get_next_line(map->fd);
		map_path[i] = line;
		i++;
	}
	ft_path_finding2(map, map_path, co);
	return ;
}
