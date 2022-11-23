/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:37:48 by merlinbourg       #+#    #+#             */
/*   Updated: 2022/11/23 17:42:28 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_exit_so_long(t_mlx *st)
{
	int	i;

	i = 0;
	while (i != st->map_x)
	{
		free(st->map[i]);
		i++;
	}
	free(st->map);
	mlx_destroy_window(st->p, st->win);
	free(st);
	system("leaks so_long");
	exit(EXIT_SUCCESS);
	return (0);
}

void	map_info2(t_mlx *st, char *line, int i)
{	
	while (line != NULL)
	{
		line = get_next_line(st->fd);
		free(line);
		st->map_x++;
	}
	close(st->fd);
	st->fd = open(st->map_path, O_RDONLY);
	st->map = malloc(st->map_x * sizeof(char *));
	while (i != st->map_x)
	{
		line = get_next_line(st->fd);
		st->map[i] = line;
		st->map[i][st->map_y] = '\0';
		i++;
	}
}

void	map_infos(t_mlx *st)
{
	char	*line;
	int		i;

	st->fd = open(st->map_path, O_RDONLY);
	line = get_next_line(st->fd);
	st->map_y = ft_strlen_back(line);
	free(line);
	st->map_x = 0;
	i = 0;
	map_info2(st, line, i);
	close(st->fd);
}

void	map_c_count(t_mlx *st)
{
	int	i;
	int	j;

	i = 0;
	while (i != st->map_x)
	{
		j = 0;
		while (j != st->map_y)
		{
			if (st->map[i][j] == 'C')
				st->c_number++;
			j++;
		}
		i++;
	}
}

void	render_map2(t_mlx *st, int i, int j)
{
	mlx_put_image_to_window(st->p, st->win, st->img_ground,
		j * 64, i * 64);
	if (st->map[i][j] == '1')
		mlx_put_image_to_window(st->p, st->win, st->img_wall,
			j * 64, i * 64);
	if (st->map[i][j] == 'P')
	{
		st->player_x = i;
		st->player_y = j;
		mlx_put_image_to_window(st->p, st->win,
			st->img_nain, j * 64, i * 64);
	}
	if (st->map[i][j] == 'E')
		mlx_put_image_to_window(st->p, st->win,
			st->img_door, j * 64, i * 64);
	if (st->map[i][j] == 'C')
		mlx_put_image_to_window(st->p, st->win,
			st->img_alcool, j * 64, i * 64);
}
