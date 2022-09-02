
#include "../_headers/cub3d.h"


// Just rewinded how to use mlx there.
// Destroy when work it seriously.


int	init_window(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		return (1);
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!mlx_data->win)
		return (1);
	for (size_t i = 150; i < 250; i++)
	{
		for (size_t j = 350; j < 550; j++)
		{
			mlx_pixel_put(mlx_data->mlx, mlx_data->win, i, j, 0x00FF0000);
		}
	}
	return (0);
}

int	end_program_hook(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
		//clear_on_exit();
		exit(0);
	}
	
	return (0);
}

int	body(t_mlx_data *mlx_data)
{
	mlx_key_hook(mlx_data->win, end_program_hook, mlx_data);
	mlx_loop(mlx_data->mlx);
	return (0);
}

int	main()
{
	t_mlx_data	mlx_data;

	if (init_window(&mlx_data))
	{
		printf("Error: init failed\n");
		return (1);
	}
	do_smt(&mlx_data);
	return (body(&mlx_data));
}
