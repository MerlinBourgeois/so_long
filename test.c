#include "so_long.h"

typedef struct s_general
{
	void			*p;
	void			*win;
	void			*img;
	void			*img2;
}	t_general;

int fun(int keycode, t_general *p)
{
	int w,h;
	static int i;
	i = 0;
	if (keycode == 1)
	{
		printf("CLICK !\n");
		printf("[%p]\n", p);
		void *img2 = mlx_xpm_file_to_image(p->p, "includes/img/test2.xpm", &w, &h);
		mlx_put_image_to_window(p->p, p->win, p->img2, 0, 0);
		//mlx_destroy_image(p->p, p->img);
	}
	return (0);
}

int main(void)
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*img2;
	int		w, h;
	int		i;
	t_general *st;
	// t_general *p;

	st = malloc(sizeof(t_general));

	mlx = mlx_init();
	i = 0;
	win = mlx_new_window(mlx, 256, 256, "Michel le Lama BG");
	img = mlx_xpm_file_to_image(mlx, "includes/img/test.xpm", &w, &h);
	img2 = mlx_xpm_file_to_image(mlx, "includes/img/test2.xpm", &w, &h);
	st->win = win;
	st->img = img;
	st->img2 = img2;
	st->p = mlx;
	// p = &st;
	printf("[%p]\n", &st);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_put_image_to_window(mlx, win, img2, 0, 64);
	mlx_key_hook(win, fun, st);
	mlx_loop(mlx);
	return 0;
}