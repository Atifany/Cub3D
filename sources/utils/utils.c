
#include "../_headers/cub3d.h"

void	error_die(t_mlx_data *m_d, char *error_text, int exit_status)
{
	if (m_d)
	{
		//clear_everything();
		mlx_destroy_window(m_d->mlx, m_d->win);
	}
	printf("%s", error_text);
	exit(exit_status);
}
