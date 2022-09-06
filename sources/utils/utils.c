
#include "../_headers/cub3d.h"

double	dabs(double x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	set_player_transform(t_game_data *g_d, t_point position, int view_angle)
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
	g_d->player = NULL;
	g_d->resolution = (t_point){1920, 1080};
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	destroy_g_d(t_game_data *g_d)
{
	if (g_d->map)
		free_array(g_d->map);
}

void	error_die(t_game_data *g_d, char *error_text, int exit_status)
{
	if (g_d && g_mlx)
	{
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		// destroy_textures();
		free(g_mlx);
		destroy_g_d(g_d);
	}
	printf("%s", error_text);
	exit(exit_status);
}
