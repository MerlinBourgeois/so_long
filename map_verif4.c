/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:57:46 by merlinbourg       #+#    #+#             */
/*   Updated: 2022/11/16 19:05:43 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_path_finding_alredy(int y, int x, t_map_corr *chain)
{
	t_map_corr	*l;

	l = chain;
	if (!chain)
		return (1);
	while (l != NULL)
	{
		if (x == l->x && y == l->y)
			return (1);
		l = l->next;
	}
	return (0);
}

t_map_corr	*ft_path_finding_map_suppup(t_map_verif *map, t_map_corr *chain)
{
	t_map_corr	*l;

	l = chain;
	if (!chain)
		return (NULL);
	while (l->next->next != NULL)
		l = l->next;
	map->map_compl[map->y][map->x] = '1';
	map->x = l->x;
	map->y = l->y;
	free(l->next);
	l->next = NULL;
	return (chain);
}

int	ft_path_finding_map_search_neighbour(t_map_verif *map)
{
	int	i;

	i = 0;
	if (map->map_compl[map->y][map->x + 1] != '1')
		i++;
	if (map->map_compl[map->y][map->x - 1] != '1')
		i++;
	if (map->map_compl[map->y + 1][map->x] != '1')
		i++;
	if (map->map_compl[map->y - 1][map->x] != '1')
		i++;
	return (i);
}

void	ft_path_red(t_map_verif *map, t_map_corr *chain, t_map_corr *co)
{
	if (map->map_compl[map->y][map->x + 1] != '1'
		&& ft_path_finding_alredy(map->y, map->x + 1, chain) == 0
			&& map->map_dist[map->y][map->x + 1] < map->lower_cost)
	{
		map->lower_cost = map->map_dist[map->y][map->x + 1];
		co->x = map->x + 1;
		co->y = map->y;
	}
	if (map->map_compl[map->y][map->x - 1] != '1'
		&& ft_path_finding_alredy(map->y, map->x - 1, chain) == 0
			&& map->map_dist[map->y][map->x - 1] < map->lower_cost)
	{
		map->lower_cost = map->map_dist[map->y][map->x - 1];
		co->x = map->x - 1;
		co->y = map->y;
	}
	if (map->map_compl[map->y + 1][map->x] != '1'
		&& ft_path_finding_alredy(map->y + 1, map->x, chain) == 0
			&& map->map_dist[map->y + 1][map->x] < map->lower_cost)
	{
		map->lower_cost = map->map_dist[map->y + 1][map->x];
		co->x = map->x;
		co->y = map->y + 1;
	}
}

void	ft_path_red2(t_map_verif *map, t_map_corr *chain, t_map_corr *co)
{
	if (map->map_compl[map->y - 1][map->x] != '1'
		&& ft_path_finding_alredy(map->y - 1, map->x, chain) == 0
			&& map->map_dist[map->y - 1][map->x] < map->lower_cost)
	{
		map->lower_cost = map->map_dist[map->y - 1][map->x];
		co->x = map->x;
		co->y = map->y - 1;
	}
}
