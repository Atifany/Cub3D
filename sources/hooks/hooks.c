
#include "../_headers/cub3d.h"

int	move_player(int keycode, t_game_data *g_d)
{
	if (keycode == W)
	{
		g_d->player->position.x += (int)(5 * cos(deg_to_rad(g_d->player->view_angle + 45)));
		g_d->player->position.y += (int)(5 * sin(deg_to_rad(g_d->player->view_angle + 45)));
	}
	else if (keycode == A)
	{
		g_d->player->position.x += (int)(5 * sin(deg_to_rad(g_d->player->view_angle + 45)));
		g_d->player->position.y -= (int)(5 * cos(deg_to_rad(g_d->player->view_angle + 45)));
	}
	else if (keycode == S)
	{
		g_d->player->position.x -= (int)(5 * cos(deg_to_rad(g_d->player->view_angle + 45)));
		g_d->player->position.y -= (int)(5 * sin(deg_to_rad(g_d->player->view_angle + 45)));
	}
	else if (keycode == D)
	{
		g_d->player->position.x -= (int)(5 * sin(deg_to_rad(g_d->player->view_angle + 45)));
		g_d->player->position.y += (int)(5 * cos(deg_to_rad(g_d->player->view_angle + 45)));
	}
	else
		return (1);
	return (0);
}

int	rotate_player(int keycode, t_game_data *g_d)
{
	if (keycode == L_ARROW)
	{
		if (g_d->player->view_angle <= 0)
			g_d->player->view_angle = 360;
		else
			g_d->player->view_angle -= 10;
	}
	else if (keycode == R_ARROW)
	{
		if (g_d->player->view_angle >= 360)
			g_d->player->view_angle = 0;
		else
			g_d->player->view_angle += 10;
	}
	else
		return (1);
	return (0);
}

int	key_hook(int keycode, t_game_data *g_d)
{
	if (keycode == ESC)
		error_die(g_d, "Cub3D: Esc key was presssed.\n", 0);
	if (move_player(keycode, g_d) && rotate_player(keycode, g_d))
		printf("Uncaught key was pressed: %d\n", keycode);
	// printf("Transform:\nX=%d Y=%d\nViewAngle=%f\n",
	// 	g_d->player->position.x,
	// 	g_d->player->position.y,
	// 	g_d->player->view_angle + 45);
	return (0);
}

void	update(t_game_data *g_d)
{
	// autorotate
	// g_d->player->view_angle += 1;
	// if (g_d->player->view_angle == 361)
	// 	g_d->player->view_angle = 0;
	mlx_clear_window(g_mlx->mlx, g_mlx->win);
	draw_frame(g_d);
}

int loop_hook(t_game_data *g_d)
{
	static int clock = 0;

	if (clock++ < TICKS_PER_UPDATE)
		return 0;
	else
	{
		clock = 0;
		update(g_d);
	}
	return (0);
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, "Cub3D: Exit button was pressed.\n", 0);
	return (0);
}
