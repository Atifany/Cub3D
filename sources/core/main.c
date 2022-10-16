#include "../_headers/cub3d.h"

t_mlx_data	*g_mlx;

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

t_img	*init_textures(char *path, t_game_data *g_d)
{
	t_img	*image;
	int		a;
	int		b;

	image = malloc(sizeof(t_img));
	image->img = mlx_xpm_file_to_image(g_mlx->mlx, path, &a, &b);
	if (!image->img)
		error_die(g_d, "Cub3D: Error: Texture not found\n", 0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	free(path);
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

int	main(int argc, char **argv)
{
	t_game_data	g_d;

	printf("Cub3D: Started.\n");
	init_g_d_defaults(&g_d);
	if (init_window(&g_d))
		error_die(&g_d, "Cub3D: Error: Initialization failed.\n", 1);
	if (argc != 2)
		error_die(&g_d, "Cub3D: Error: Invalid input.\n"
			"Usage: ./cub3D [filename].cub\n", 1);
	if (!parse_file(&g_d, argv[1]))
		error_die(&g_d, "Cub3D: Error: Parsing file failed.\n", 1);
	printf("Player start transform:\nPosition={%f:%f}\nViewAngle={%f}\n",
		g_d.player->position.x,
		g_d.player->position.y,
		g_d.player->view_angle);
	return (body(&g_d));
}
