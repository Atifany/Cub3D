
#include "../_headers/cub3d.h"

int	key_hook(int keycode, t_mlx_data *m_d)
{
	if (keycode == ESC_KEY)
		error_die(m_d, "Cub3D: Esc key was presssed.\n", 0);
	return (0);
}

int	die_hook(t_mlx_data *m_d)
{
	error_die(m_d, "Cub3D: Exit button was pressed.\n", 0);
	return (0);
}
