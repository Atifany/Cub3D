#include "../_headers/cub3D.h"

int	move_player(int keycode, t_game_data *g_d)
{
	float	sin_dir;
	float	cos_dir;
	
	cos_dir = g_d->player_speed * cos(deg_to_rad(g_d->player->view_angle + 45));
	sin_dir = g_d->player_speed * sin(deg_to_rad(g_d->player->view_angle + 45));
	if (keycode == W)
	{
		g_d->player->position.x += cos_dir;
		g_d->player->position.y += sin_dir;
	}
	else if (keycode == A)
	{
		g_d->player->position.x += sin_dir;
		g_d->player->position.y -= cos_dir;
	}
	else if (keycode == S)
	{
		g_d->player->position.x -= cos_dir;
		g_d->player->position.y -= sin_dir;
	}
	else if (keycode == D)
	{
		g_d->player->position.x -= sin_dir;
		g_d->player->position.y += cos_dir;
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
			g_d->player->view_angle -= g_d->player_rot_speed;
	}
	else if (keycode == R_ARROW)
	{
		if (g_d->player->view_angle >= 360)
			g_d->player->view_angle = 0;
		else
			g_d->player->view_angle += g_d->player_rot_speed;
	}
	else
		return (1);
	return (0);
}