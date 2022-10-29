#include "../_headers/cub3d.h"

t_mlx_data	*g_mlx;

t_img *create_background(t_game_data *g_d)
{
	t_img	*image;
	int x;
	int y;

	image = malloc(sizeof(t_img));
	image->img = mlx_new_image(g_mlx->mlx, g_d->resolution.x, g_d->resolution.y);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length,
								&image->endian);
	y = 0;
	while (y < g_d->resolution.y)
	{
		x = 0;
		while (x < g_d->resolution.x)
		{
			if (y < g_d->resolution.y >> 1)
				my_pixel_put(image, x, y, darker(g_d->ceiling, (sqrt(y)) * 11));
			else
				my_pixel_put(image, x, y, darker(g_d->floor, (sqrt(g_d->resolution.y - y)) * 11));
			x++;
		}
		y++;
	}
	return (image);
}

void	null_textures()
{
	g_mlx->texture_east = NULL;
	g_mlx->texture_north = NULL;
	g_mlx->texture_south = NULL;
	g_mlx->texture_west = NULL;
}

int	init_window(t_game_data *g_d)
{
	g_mlx = (t_mlx_data *)ft_calloc(1, sizeof(t_mlx_data));
	g_mlx->mlx = mlx_init();
	if (!g_mlx->mlx)
		return (1);
	g_mlx->img = ft_calloc(1, sizeof(t_img));
	g_mlx->img->line_length = g_d->resolution.x;
	g_mlx->win = mlx_new_window(g_mlx->mlx,
			g_d->resolution.x, g_d->resolution.y, "Cub3D");
	if (!g_mlx->win)
		return (1);
	null_textures();
	return (0);
}

t_img	*init_textures(char *path)
{
	t_img	*image;
	int		a;
	int		b;

	image = malloc(sizeof(t_img));
	image->img = mlx_xpm_file_to_image(g_mlx->mlx, path, &a, &b);
	if (!image->img)
		return (NULL);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (image);
}

int	body(t_game_data *g_d)
{
	mlx_do_key_autorepeatoff(g_mlx->mlx);
	set_new_mouse_pos(g_d->resolution.x / 2, g_d->resolution.y / 2);
	mlx_mouse_hide(g_mlx->mlx, g_mlx->win);
	mlx_hook(g_mlx->win, DestroyNotify, NoEventMask, die_hook, g_d);
	mlx_hook(g_mlx->win, KeyPress, KeyPressMask, key_down_hook,
		g_d);
	mlx_hook(g_mlx->win, KeyRelease, KeyReleaseMask, key_up_hook,
		&(g_d->keys_pressed));
	mlx_hook(g_mlx->win, FocusIn, FocusChangeMask, focus_in, g_d);
	mlx_hook(g_mlx->win, FocusOut, FocusChangeMask, focus_out, g_d);
	mlx_loop_hook(g_mlx->mlx, loop_hook, g_d);
	mlx_loop(g_mlx->mlx);
	return (0);
}

int input_start(int argc, char **argv)
{
	t_game_data	*g_d;
	int parse_ret;

	printf("Cub3D: Started.\n");
	g_d = ft_calloc(1, sizeof(t_game_data));
	init_g_d_defaults(g_d);
	if (init_window(g_d))
		error_die(g_d, 0, 1);
	if (argc != 2)
		error_die(g_d, 1, 1);
	parse_ret = parse_file(g_d, argv[1]);
	if (parse_ret >= 0)
		error_die(g_d, parse_ret, 1);
	g_mlx->bg = create_background(g_d);
	return (body(g_d));
}
