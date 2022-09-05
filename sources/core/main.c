
#include "../_headers/cub3d.h"

t_mlx_data	*g_mlx;

int	init_window(t_game_data *g_d)
{
	g_mlx = (t_mlx_data *)ft_calloc(1, sizeof(t_mlx_data));
	g_mlx->mlx = mlx_init();
	if (!g_mlx->mlx)
		return (1);
	g_mlx->line_length = g_d->resolution.x;
	g_mlx->win = mlx_new_window(g_mlx->mlx, g_d->resolution.x, g_d->resolution.y, "Cub3D");
	if (!g_mlx->win)
		return (1);
	// for (size_t i = 0; i < 1900; i++)
	// {
	// 	for (size_t j = 0; j < 1000; j++)
	// 	{
	// 		mlx_pixel_put(g_mlx->mlx, g_mlx->win, i, j, 0x00FFFF00);
	// 	}
	// }
	return (0);
}



int	body(t_game_data *g_d)
{
	mlx_key_hook(g_mlx->win, key_hook, g_d);
	mlx_hook(g_mlx->win, 17, 0L, die_hook, g_d);
	mlx_loop_hook(g_mlx->mlx, loop_hook, g_d);
	mlx_loop(g_mlx->mlx);

	return (0);
}

int	main(int argc, char **argv)
{
	t_game_data	g_d;
	char	*file_name;
	char	*maps_path;

	printf("Cub3D: Started.\n");
	init_g_d_defaults(&g_d);
	if (!is_valid_input(argc))
		error_die(&g_d, "Cub3D: Error: Invalid input.\nUsage: ./cub3D [filename].cub", 1);
	maps_path = ft_strdup("maps/");
	file_name = gnl_join(&maps_path, ft_strdup(argv[1]), ft_strlen(argv[1]));
	if (!parse_file(&g_d, file_name))
		error_die(&g_d, "Cub3D: Error: Parsing file failed.\n", 1);
	if (init_window(&g_d))
		error_die(&g_d, "Cub3D: Error: Initialization failed.\n", 1);
	// g_d.player = malloc(sizeof(t_transform));
	// g_d.player->position.x = 70;
	// g_d.player->position.y = 70;
	// g_d.player->view_angle = 0;
	
	// g_d.map = calloc(65*5, sizeof(int *));
	// for (int i = 0; i < 64 * 5; i++)
	// 	g_d.map[i] = calloc(65*5,sizeof(char));
	
	// for (int i = 0; i < 64 * 5; i++)
	// {
	// 	g_d.map[0][i] = 1;
	// 	g_d.map[64*4][i] = 1;
	// 	g_d.map[i][0] = 1;
	// 	g_d.map[i][64*4] = 1;
	// }
	// printf("%d\n", g_d.map);
	// printf("%d\n", g_d.map[0][0]);
	
	printf("Player start transform:\nPosition={%d:%d}\nViewAngle={%f}\n",
		g_d.player->position.x,
		g_d.player->position.y,
		g_d.player->view_angle);
	//draw_frame(&g_d);
	return (body(&g_d));
}
