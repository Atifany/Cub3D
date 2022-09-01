
#include "../headers/cub3d.h"


// Just rewinded how to use mlx there.
// Destroy when work it seriously.


bool	display_window()
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (false);
	win = mlx_new_window(mlx, 1920, 1024, "cub3D");
	if (!win)
		return (false);
	//mlx_clear_window(mlx, win);  // <-- destroys window
	for (size_t i = 150; i < 250; i++)
	{
		for (size_t j = 350; j < 550; j++)
		{
			mlx_pixel_put(mlx, win, i, j, 0x00FF0000);
		}
	}
	mlx_loop(mlx);
	return (true);
}

int	main()
{
	printf("\nProgram started\n");
	if (!display_window())
		printf("Error: init failed\n");
	printf("\nInit success\n");
}
