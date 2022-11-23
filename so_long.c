/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:31:59 by merlinbourg       #+#    #+#             */
/*   Updated: 2022/11/23 18:38:26 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_mlx *st)
{
	int	i;
	int	j;

	i = 0;
	while (i != st->map_x)
	{
		j = 0;
		while (j != st->map_y)
		{
			render_map2(st, i, j);
			j++;
		}
		i++;
	}
}

void	restore_previous_image(t_mlx *st)
{
	if (st->map[st->player_x][st->player_y] == '0'
		|| st->map[st->player_x][st->player_y] == 'P'
			|| st->map[st->player_x][st->player_y] == 'C')
		mlx_put_image_to_window(st->p, st->win,
			st->img_ground, st->player_y * 64, st->player_x * 64);
	if (st->map[st->player_x][st->player_y] == 'E')
	{
		mlx_put_image_to_window(st->p, st->win, st->img_ground,
			st->player_y * 64, st->player_x * 64);
		mlx_put_image_to_window(st->p, st->win, st->img_door,
			st->player_y * 64, st->player_x * 64);
	}
}

void	move_player2(int keycode, t_mlx *st)
{
	if (keycode == 2 && st->map[st->player_x][st->player_y + 1] != '1')
	{
		restore_previous_image(st);
		mlx_put_image_to_window(st->p, st->win, st->img_nain,
			(st->player_y + 1) * 64, st->player_x * 64);
		st->player_y++;
	}
	if (keycode == 0 && st->map[st->player_x + 1][st->player_y] != '1')
	{
		restore_previous_image(st);
		mlx_put_image_to_window(st->p, st->win, st->img_nain,
			st->player_y * 64, (st->player_x + 1) * 64);
		st->player_x++;
	}
	if (keycode == 7 && st->map[st->player_x][st->player_y - 1] != '1')
	{
		restore_previous_image(st);
		mlx_put_image_to_window(st->p, st->win, st->img_nain,
			(st->player_y - 1) * 64, st->player_x * 64);
		st->player_y--;
	}
}

int	move_player(int keycode, t_mlx *st)
{
	if (st->map[st->player_x][st->player_y] == 'C')
	{
		st->c_number--;
		st->map[st->player_x][st->player_y] = '0';
	}
	if (st->map[st->player_x][st->player_y] == 'E' && st->c_number == 0)
		free_exit_so_long(st);
	if (keycode == 1 && st->map[st->player_x - 1][st->player_y] != '1')
	{
		restore_previous_image(st);
		mlx_put_image_to_window(st->p, st->win, st->img_nain,
			st->player_y * 64, (st->player_x - 1) * 64);
		st->player_x--;
	}
	move_player2(keycode, st);
	if (keycode == 53)
		free_exit_so_long(st);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*st;

	st = malloc(sizeof(t_mlx));
	if (argc != 2)
	{
		ft_putstr_fd("ERROR\nUn arguments attendus.\n", 1);
		exit(EXIT_FAILURE);
	}
	st->map_path = argv[1];
	ft_init_verif(st->map_path);
	map_infos(st);
	map_c_count(st);
	st->p = mlx_init();
	st->win = mlx_new_window(st->p, st->map_y * 64, st->map_x * 64, "So_long");
	st->img_alcool = mlx_xpm_file_to_image(st->p,
			"includes/img/alcool.xpm", &st->w, &st->h);
	st->img_door = mlx_xpm_file_to_image(st->p,
			"includes/img/door.xpm", &st->w, &st->h);
	st->img_ground = mlx_xpm_file_to_image(st->p,
			"includes/img/ground.xpm", &st->w, &st->h);
	st->img_nain = mlx_xpm_file_to_image(st->p,
			"includes/img/nain.xpm", &st->w, &st->h);
	st->img_wall = mlx_xpm_file_to_image(st->p,
			"includes/img/wall.xpm", &st->w, &st->h);
	render_map(st);
	mlx_key_hook(st->win, move_player, st);
	mlx_hook(st->win, 17, 0, free_exit_so_long, st);
	mlx_loop(st->p);
}
