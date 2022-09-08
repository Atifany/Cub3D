#include "../_headers/cub3D.h"

static t_point	is_collsion(t_game_data *g_d, t_fpoint new_pos)
{
	int i;
	int j;
	int imax;
	int jmax;

	imax = (int)(new_pos.x + (g_d->player->size.x) / 2);
	jmax = (int)(new_pos.y + (g_d->player->size.y) / 2);
	i = (int)fto_pos((new_pos.x - (g_d->player->size.x) / 2));
	while (g_d->map[i] && i < imax)
	{
		j = (int)fto_pos(new_pos.y - (g_d->player->size.y) / 2);
		while (g_d->map[i][j] && j < jmax)
		{
			if (g_d->map[i][j] == '1')
				return ((t_point){i, j});
			j++;
		}
		i++;
	}
	return ((t_point){-1, -1});
}

// ADD COLLISIONS!!
// add a case if 'W' and 'D' are pressed together.
int	move_player(int keycode, t_game_data *g_d)
{
	float		sin_dir;
	float		cos_dir;
	t_point		ret;

	cos_dir = g_d->player_speed * cos(deg_to_rad(g_d->player->view_angle + 45));
	sin_dir = g_d->player_speed * sin(deg_to_rad(g_d->player->view_angle + 45));
	if (keycode == W)
	{
		ret = is_collsion(g_d, (t_fpoint){
			g_d->player->position.x + cos_dir,
			g_d->player->position.y + sin_dir});
		if (ret.x < 0)
		{
			g_d->player->position.x += cos_dir;
			g_d->player->position.y += sin_dir;
		}
		else
		{
			printf("Player position={%f, %f}\n",
				g_d->player->position.x, g_d->player->position.y);
			printf("Collision at point={%d,%d}\n",
				ret.x, ret.y);
		}
	}
	else if (keycode == A)
	{
		ret = is_collsion(g_d, (t_fpoint){
			g_d->player->position.x + cos_dir,
			g_d->player->position.y + sin_dir});
		if (ret.x < 0)
		{
			g_d->player->position.x += sin_dir;
			g_d->player->position.y -= cos_dir;
		}
		else
		{
			printf("Player position={%f, %f}\n",
				g_d->player->position.x, g_d->player->position.y);
			printf("Collision at point={%d,%d}\n",
				ret.x, ret.y);
		}
	}
	else if (keycode == S)
	{
		ret = is_collsion(g_d, (t_fpoint){
			g_d->player->position.x + cos_dir,
			g_d->player->position.y + sin_dir});
		if (ret.x < 0)
		{
			g_d->player->position.x -= cos_dir;
			g_d->player->position.y -= sin_dir;
		}
		else
		{
			printf("Player position={%f, %f}\n",
				g_d->player->position.x, g_d->player->position.y);
			printf("Collision at point={%d,%d}\n",
				ret.x, ret.y);
		}
	}
	else if (keycode == D)
	{
		ret = is_collsion(g_d, (t_fpoint){
			g_d->player->position.x + cos_dir,
			g_d->player->position.y + sin_dir});
		if (ret.x < 0)
		{
			g_d->player->position.x -= sin_dir;
			g_d->player->position.y += cos_dir;
		}
		else
		{
			printf("Player position={%f, %f}\n",
				g_d->player->position.x, g_d->player->position.y);
			printf("Collision at point={%d,%d}\n",
				ret.x, ret.y);
		}
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
