#include "../_headers/cub3d.h"

double	dabs(double x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

float	fto_pos(float x)
{
	if (x <= 0.0f)
		x = 0;
	return (x);
}

void	set_player_transform(t_game_data *g_d,
	t_fpoint position, int view_angle)
{
	if (!g_d->player)
		g_d->player = (t_transform *)ft_calloc(1, sizeof(t_transform));
	g_d->player->position = position;
	g_d->player->view_angle = view_angle;
}

void	init_g_d_defaults(t_game_data *g_d)
{
	g_d->map = NULL;
	g_d->fov = 90;
	g_d->player = (t_transform *)ft_calloc(1, sizeof(t_transform));
	//printf("{%-20s%p}\n", "g_d->player:", g_d->player);
	g_d->player->position = (t_fpoint){0.0f, 0.f};
	g_d->player->view_angle = 0.0f;
	g_d->player->size = (t_fpoint){
		(float)(MAP_RES / PLAYER_SIZE_MULTY),
		(float)(MAP_RES / PLAYER_SIZE_MULTY)};
	g_d->res = (t_point){1920, 1080};
	g_d->keys_pressed = NULL;
	g_d->player_rot_speed = 0.1f;
	g_d->player_speed = 20.0f;
	g_d->is_focused = true;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}