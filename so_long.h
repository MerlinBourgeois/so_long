/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:33:57 by mebourge          #+#    #+#             */
/*   Updated: 2022/11/23 18:43:05 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "includes/lib/mlx/mlx.h"
# include "includes/lib/Libft/libft.h"
# include "includes/lib/Libft/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_mlx
{
	void			*p;
	void			*win;
	void			*img_alcool;
	void			*img_door;
	void			*img_nain;
	void			*img_wall;
	void			*img_ground;
	int				w;
	int				h;
	char			*map_path;
	int				fd;
	char			**map;
	int				map_x;
	int				map_y;
	int				player_x;
	int				player_y;
	int				c_number;

}	t_mlx;

typedef struct s_map_verif
{
	int		player;
	int		out;
	int		fd;
	int		error;
	char	*map_path;
	int		map_x;
	int		map_y;
	int		x;
	int		y;
	int		mana_x;
	int		mana_y;
	int		out_x;
	int		out_y;
	int		dist;
	int		map_mapleng;
	int		lower_cost;
	int		**map_dist;
	char	**map_compl;
	int		nb_char_c;
	int		nb_colectible;
}	t_map_verif;

typedef struct s_map_corr
{
	int					x;
	int					y;
	struct s_map_corr	*next;
}	t_map_corr;

int			free_exit_so_long(t_mlx *st);
void		map_info2(t_mlx *st, char *line, int i);
void		map_infos(t_mlx *st);
void		map_c_count(t_mlx *st);
void		render_map2(t_mlx *st, int i, int j);
int			ft_init_verif(char *path);
void		verif_around_map(t_map_verif *map);
void		verif_around_map_bottom(t_map_verif *map);
void		verif_around_map_bottom2(t_map_verif *map, char *line);
void		verif_around_map_middle(t_map_verif *map);
void		verif_around_map_middle2(t_map_verif *map, char *line);
void		verif_around_map_top(t_map_verif *map);
void		ft_get_out(char *line);
void		ft_path_red2(t_map_verif *map, t_map_corr *chain, t_map_corr *co);
void		ft_path_red(t_map_verif *map, t_map_corr *chain, t_map_corr *co);
int			ft_path_finding_map_search_neighbour(t_map_verif *map);
t_map_corr	*ft_path_finding_map_suppup(t_map_verif *map, t_map_corr *chain);
int			ft_path_finding_alredy(int y, int x, t_map_corr *chain);
void		ft_path_finding_map_locate(t_map_verif *map, char c);
void		ft_path_finding_map_put_tab(t_map_verif *map);
void		ft_path_finding_map_manathan(t_map_verif *map);
t_map_corr	*lstadd_back(t_map_corr *chain, t_map_corr *co);
t_map_corr	*get_last(t_map_corr *chain);
void		ft_path_finding(t_map_verif *map);
void		verif_around_map(t_map_verif *map);
size_t		ft_strlen_back(const char *s);

#endif