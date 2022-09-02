
#include "../_headers/cub3d.h"

int	key_hook(int keycode, t_game_data *g_d)
{
	if (keycode == ESC_KEY)
		error_die(g_d, "Cub3D: Esc key was presssed.\n", 0);
	return (0);
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, "Cub3D: Exit button was pressed.\n", 0);
	return (0);
}
