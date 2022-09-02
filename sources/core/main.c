
#include "../_headers/cub3d.h"

int	init_window(t_mlx_data *m_d)
{
	m_d->mlx = mlx_init();
	if (!m_d->mlx)
		return (1);
	m_d->win = mlx_new_window(m_d->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!m_d->win)
		return (1);
	return (0);
}

int	body(t_mlx_data *m_d)
{
	mlx_key_hook(m_d->win, key_hook, m_d);
	mlx_hook(m_d->win, 17, 0L, die_hook, m_d);
	mlx_loop(m_d->mlx);
	return (0);
}

int	main()
{
	t_mlx_data	m_d;

	if (init_window(&m_d))
		error_die(&m_d, "Cub3D: Error: Initialization failed.\n", 1);
	return (body(&m_d));
}
