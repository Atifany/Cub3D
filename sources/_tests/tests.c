
# include "../_headers/cub3d.h"
# include "../_headers/colors.h"
# include <signal.h>
# include <sys/wait.h>

int test_number;
char *tested_func;

void sigsegv_exit()
{
	printf("%sSIGSEGV%s %s failed test:%d\n", BYEL, NC, tested_func, test_number);
	exit(1);
}

bool test_int(int expected, int recieved)
{
	if (expected != recieved)
		return (false);
	return (true);
}

bool test_player_transform(t_transform* expected, t_transform* recieved)
{
	if ((expected == NULL && recieved != NULL)
		|| (expected != NULL && recieved == NULL))
		return (false);
	if (expected->position.x != recieved->position.x
		|| expected->position.y != recieved->position.y)
		return (false);
	if (expected->view_angle != recieved->view_angle)
		return (false);
	return (true);
}

bool test_map(char** expected, char** recieved)
{
	int i = 0; int j = 0;

	if (expected == NULL && recieved == NULL)
		return (true);
	if ((expected == NULL && recieved != NULL)
		|| (expected != NULL && recieved == NULL))
		return (false);
	while (expected[i] && recieved[i])
	{
		j = 0;
		while (expected[i][j] && recieved[i][j])
		{
			if (expected[i][j] != recieved[i][j])
				{ printf("0[%d:%d]\n", i / MAP_RES, j / MAP_RES); return (false); }
			j++;
		}
		if (expected[i][j] != recieved[i][j])
			{ printf("1[%d:%d][%d:%d]\n", i / MAP_RES, j / MAP_RES, expected[i][j], recieved[i][j]); return (false); }
		i++;
	}
	if (expected[i] != recieved[i])
		{ printf("2[%d:%d]\n", i / MAP_RES, j / MAP_RES); return (false); }
	return (true);
}

bool test_bool(bool expected, bool recieved)
{
	if (expected == recieved)
		return (true);
	return (false);
}

void t_is_valid_file()
{
	char *test_value;

	test_number = 1;
	{	
		test_value = "map.cub";
		if (test_bool(true, is_valid_file(test_value)) == false)
			return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
				BRED, NC, test_number));
	}

	test_number = 2;
	{	
		test_value = ".cub";
		if (test_bool(false, is_valid_file(test_value)) == false)
			return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
				BRED, NC, test_number));
	}

	test_number = 3;
	{
		test_value = "";
		if (test_bool(false, is_valid_file(test_value)) == false)
			return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
				BRED, NC, test_number));
	}

	test_number = 4;
	{
		test_value = "map";
		if (test_bool(false, is_valid_file(test_value)) == false)
			return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
				BRED, NC, test_number));
	}

	test_number = 5;
	{	
		test_value = NULL;
		if (test_bool(false, is_valid_file(test_value)) == false)
			return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
				BRED, NC, test_number));
	}

	printf("%sV%s is_valid_file() tests:%d\n", BGRN, NC, test_number);
}

void t_is_valid_map()
{
	char	**test_map;

	test_number = 1;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1111");
		test_map[1] = ft_strdup("10S1");
		test_map[2] = ft_strdup("1111");
		if (test_bool(true, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}
	
	test_number = 2;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("011");
		test_map[1] = ft_strdup("1S1");
		test_map[2] = ft_strdup("111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 3;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("N11");
		test_map[1] = ft_strdup("101");
		test_map[2] = ft_strdup("111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 4;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("11");
		test_map[1] = ft_strdup("1N1");
		test_map[2] = ft_strdup("111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 5;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1 1");
		test_map[1] = ft_strdup("1N1");
		test_map[2] = ft_strdup("111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 6;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("111");
		test_map[1] = ft_strdup(" S1");
		test_map[2] = ft_strdup("111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 7;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("111");
		test_map[1] = ft_strdup("1E1");
		test_map[2] = ft_strdup("111");
		if (test_bool(true, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 8;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1");
		test_map[1] = ft_strdup("11E1");
		test_map[2] = ft_strdup("1111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 9;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1111");
		test_map[1] = ft_strdup("11W1");
		test_map[2] = ft_strdup("1");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 10;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1111");
		test_map[1] = ft_strdup("1W");
		test_map[2] = ft_strdup("1111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 11;
	{
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("111");
		test_map[1] = ft_strdup("1R1");
		test_map[2] = ft_strdup("111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 12;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("S");
		test_map[1] = ft_strdup("");
		test_map[2] = ft_strdup("1111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 13;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1111");
		test_map[1] = ft_strdup("1011");
		test_map[2] = ft_strdup("1111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 14;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("11");
		test_map[1] = ft_strdup("1N");
		test_map[2] = ft_strdup("111111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 15;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1111");
		test_map[1] = ft_strdup("1NS1");
		test_map[2] = ft_strdup("111111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 16;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("1111");
		test_map[1] = ft_strdup("1WW1");
		test_map[2] = ft_strdup("111111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 17;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("11111");
		test_map[1] = ft_strdup("1W10");
		test_map[2] = ft_strdup("11111");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 18;
	{	
		test_map = ft_calloc(4, sizeof(char *));
		test_map[0] = ft_strdup("");
		test_map[1] = ft_strdup("");
		test_map[2] = ft_strdup("");
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}

	test_number = 19;
	{		
		test_map = ft_calloc(4, sizeof(char *));
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
		free_array(test_map);
	}
	
	test_number = 20;
	{	
		test_map = NULL;
		if (test_bool(false, is_valid_map(test_map)) == false)
			return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
				BRED, NC, test_number));
	}

	printf("%sV%s is_valid_map() tests:%d\n", BGRN, NC, test_number);
}

void t_parse_file()
{
	char** map;
	char* file_path;
	t_game_data* g_d;
	t_transform* player_ref;

	test_number = 1;
	{
		player_ref = ft_calloc(1, sizeof(t_transform));
		map = ft_calloc(14, sizeof(char*));
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map1.cub";
		if (test_int(-1, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		map[0] =	ft_strdup("11111");
		map[1] =	ft_strdup("1");
		map[2] =	ft_strdup("1");
		map[3] =	ft_strdup("1");
		map[4] =	ft_strdup("11111111111");
		map[5] =	ft_strdup("10000000001");
		map[6] =	ft_strdup("11110000001");
		map[7] =	ft_strdup("10000000011111111");
		map[8] =	ft_strdup("1000000011");
		map[9] =	ft_strdup("1110000111");
		map[10] =	ft_strdup("1000000001");
		map[11] =	ft_strdup("111111111111111");
		map[12] =	ft_strdup("1");
		map = multiply_size(map);
		if (test_map(map, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		player_ref->position = (t_fpoint){6 * MAP_RES - (MAP_RES / 2),
			2 * MAP_RES - (MAP_RES / 2)};
		player_ref->view_angle = 90.0f;
		if (test_player_transform(player_ref, g_d->player) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid player)\n",
				BRED, NC, test_number));
		if (test_int(0xFFFFFF, g_d->floor) == false
			|| test_int(0x00010C, g_d->ceiling) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid color)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		free(player_ref);
		free_array(map);
		destroy_g_d(g_d);
	}

	test_number = 2;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		file_path = "keke";
		if (test_int(2, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		destroy_g_d(g_d);
	}

	test_number = 3;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		file_path = "maps/map_inacceseble.cub";
		if (test_int(3, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		destroy_g_d(g_d);
	}

	test_number = 4;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_invalid_map.cub";
		if (test_int(4, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	test_number = 5;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_invalid_floor.cub";
		if (test_int(5, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	test_number = 6;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_invalid_ceiling.cub";
		if (test_int(6, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	test_number = 7;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_invalid_head.cub";
		if (test_int(7, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	test_number = 8;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_invalid_texture.cub";
		if (test_int(10, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	test_number = 9;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_empty.cub";
		if (test_int(7, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	test_number = 10;
	{
		g_d = ft_calloc(1, sizeof(t_game_data));
		init_g_d_defaults(g_d);
		init_window(g_d);
		file_path = "maps/map_empty_map.cub";
		if (test_int(4, parse_file(g_d, file_path)) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (return value)\n",
				BRED, NC, test_number));
		if (test_map(NULL, g_d->map) == false)
			return ((void)printf("%sX%s parse_file() failed test:%d (invalid map)\n",
				BRED, NC, test_number));
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		destroy_g_d(g_d);
	}

	printf("%sV%s parse_file() tests:%d\n", BGRN, NC, test_number);
}

void run_func_tests(void (*f)(void), int tests_amount)
{
	int child_pid;
	int status;

	child_pid = fork();
	// child
	if (child_pid == 0)
	{
		signal(SIGSEGV, sigsegv_exit);
		f();
		exit(test_number);
	}
	// parent
	else
	{
		wait(&status);
		if (status>>8 != tests_amount)
			printf("%sX%s %s (unexpected exit)\n",
				BRED, NC, tested_func);
	}
	
}

int main()
{
	tested_func = "is_valid_file()";
	run_func_tests(t_is_valid_file, 5);
	tested_func = "is_valid_map()";
	run_func_tests(t_is_valid_map, 20);
	tested_func = "parse_file()";
	run_func_tests(t_parse_file, 10);

	return (0);
}
