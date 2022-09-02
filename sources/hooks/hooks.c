
#include "../_headers/cub3d.h"

int	key_hook(int keycode, t_game_data *g_d)
{
	if (keycode == ESC_KEY)
		error_die(g_d, "Cub3D: Esc key was presssed.\n", 0);
	if (keycode == 2)
	{
		g_d->player->position.x -= 5;
	}
	if (keycode == 0)
	{
		g_d->player->position.x += 5;
	}
	if (keycode == 13)
	{
		g_d->player->position.y += 5;
	}
	if (keycode == 1)
	{
		g_d->player->position.y -= 5;
	}
	return (0);
}

int loop_hook(t_game_data *g_d)
{
	static int clock = 0;

	if (clock++ < 2000)
		return 0;
	else
	{
		clock = 0;
		// g_d->player->view_angle += 1;
		// if (g_d->player->view_angle == 361)
		// 	g_d->player->view_angle = 0;
		mlx_clear_window(g_mlx->mlx, g_mlx->win);
		draw_frame(g_d);
	}
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, "Cub3D: Exit button was pressed.\n", 0);
	return (0);
}
