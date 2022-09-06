
#include "../_headers/cub3d.h"

void	display_charpp(char **arr)
{
	int i = 0;

	if (!arr || !*arr)
		printf("DEBUG: array is empty.\n");
	while (arr[i])
	{
		printf("%s|\n", arr[i]);
		i++;
	}
}

void	ddisplay_charpp(char **arr)
{
	int j = 0;
	int i = 0;

	if (!arr || !*arr)
		printf("DEBUG: array is empty.\n");
	while (arr[i])
	{
		j = 0;
		while (j < 5 * MAP_RES)
		{
			printf("%d", arr[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
}

// static int	usefull_len(char *line)
// {
// 	int	i;
// 	int ans;
// 
// 	ans = 0;
// 	i = (int)ft_strlen(line) - 1;
// 	while (ft_isspace(line[i]))
// 		i--;
// 	ans += i + 1;
// 	if (ans == 0)
// 	{
// 		printf("Line usefull length is: %d\n", ans);
// 		return (ans);
// 	}
// 	i = 0;
// 	while (ft_isspace(line[i]))
// 		i++;
// 	ans -= i;
// 	printf("Line usefull length is: %d\n", ans);
// 	return (ans);
// }

static int	count_items_charpp(char **charpp)
{
	int	i;

	i = 0;
	while (charpp && charpp[i])
		i++;
	return (i);
}

static char	*multiply_line(char *line)
{
	int		i;
	int		j;
	char	*extended_line;

	extended_line = (char *)ft_calloc(
		ft_strlen(line) * MAP_RES + 1, sizeof(char));
	i = 0;
	while (line[i])
	{
		j = i * MAP_RES;
		while (j < (i + 1) * MAP_RES)
			extended_line[j++] = line[i];
		i++;
	}
	return (extended_line);
}

static bool	is_spawner(char c)
{
	if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
		return (true);
	return (false);
}

static int	find_left_border(char *line)
{
	int	ans;

	ans = 0;
	while (line[ans] && ft_isspace(line[ans]))
		ans++;
	return (ans);
}

static int	find_right_border(char *line)
{
	int	ans;

	ans = ft_strlen(line) - 1;
	while (line[ans] && ft_isspace(line[ans]))
		ans--;
	return (ans);
}

static char	**read_file(char *file_path)
{
	int		i;
	int		fd;
	char	*str;
	char	**file_text;

	file_text = NULL;
	fd = open(file_path, O_RDONLY, 0777);
	if (fd == -1)
		return (NULL);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		i++;
		file_text = realloc(file_text, i * sizeof(char *));
		file_text[i - 1] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
	}
	file_text = realloc(file_text, (i + 1) * sizeof(char *));
	file_text[i] = NULL;
	return (file_text);
}

static char	**cut_trailings(char **file_text)
{
	int		leftest_border;
	int		rightest_border;
	int		i;
	char	**cut_text;

	leftest_border = INT_MAX;
	rightest_border = 0;
	i = 0;
	while (file_text[i])
	{
		if (find_left_border(file_text[i]) < leftest_border)
			leftest_border = find_left_border(file_text[i]);
		if (find_right_border(file_text[i]) > rightest_border)
			rightest_border = find_right_border(file_text[i]);
		i++;
	}
	cut_text = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (file_text[i])
	{
		cut_text[i] = ft_substr(file_text[i],
			leftest_border, find_right_border(file_text[i]) - leftest_border + 1);
		i++;
	}
	cut_text[i] = NULL;
	return (cut_text);
}

static void	clean_spaces(t_game_data *g_d, char **cut_text)
{
	t_point	position;
	int		view_angle;
	int		i;
	int		j;

	view_angle = 135;
	i = 0;
	while (cut_text[i])
	{
		j = 0;
		while (cut_text[i][j])
		{
			if (ft_isspace(cut_text[i][j]))
				cut_text[i][j] = '1';
			else if (is_spawner(cut_text[i][j]))
			{
				position.x =
					(i + 1) * MAP_RES - MAP_RES / 2;
				position.y =
					(j + 1) * MAP_RES - MAP_RES / 2;
				if (cut_text[i][j] == 'W')
					view_angle = 225;
				else if (cut_text[i][j] == 'E')
					view_angle = 45;
				else if (cut_text[i][j] == 'S')
					view_angle = 315;
				set_player_transform(g_d, position, view_angle);
				cut_text[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

static char	**multiply_size(char **cut_text)
{
	int		j;
	int		i;
	char	*line_cpy;
	char	**map;

	map = (char **)ft_calloc(
		count_items_charpp(cut_text) * MAP_RES + 1, sizeof(char *));
	i = 0;
	while (cut_text[i])
	{
		line_cpy = multiply_line(cut_text[i]);
		j = i * MAP_RES;
		while (j < (i + 1) * MAP_RES)
			map[j++] = ft_strdup(line_cpy);
		free(line_cpy);
		i++;
	}
	return (map);
}

static void	to_binary(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j] -= '0';
			j++;
		}
		i++;
	}
}

static bool	is_valid_map(char **file_text)
{
	int	i;
	int	j;

	i = 0;
	while (file_text[i])
	{
		j = 0;
		while (file_text[i][j])
		{
			if (!ft_isspace(file_text[i][j]) && !is_spawner(file_text[i][j]) &&
				file_text[i][j] != '0' && file_text[i][j] != '1')
				return (false);
			// For each tile, check all four its adjustment tiles.
			// And only check if current tile is a space.
			// it is going to be a biiiiig if clause
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_file(t_game_data *g_d, char *file_path)
{
	char	**file_text;
	char	**cut_text;

	if (!is_valid_file(file_path))
		return (false);
	file_text = read_file(file_path);
	if (!file_text)
		error_die(g_d, "Cub3D: Error: Cannot open given file.\n", 1);
	// printf("Raw:\n");
	// display_charpp(file_text);

	// for validation: no ISSPACE and '0' symbols are to stay next to each other.
	// and do not forget to check forbidden symbols.
	if (!is_valid_map(file_text))
		error_die(g_d, "Cub3D: Error: Invalid map.\n", 1);

	cut_text = cut_trailings(file_text);
	free_array(file_text);
	//printf("Cut:\n");
	//display_charpp(cut_text);

	clean_spaces(g_d, cut_text);
	//printf("Cleaned:\n");
	//display_charpp(cut_text);

	g_d->map = multiply_size(cut_text);
	free_array(cut_text);
	//printf("Ready to use:\n");
	//display_charpp(g_d->map);

	to_binary(g_d->map);

	//printf("\n\n");
	//ddisplay_charpp(g_d->map);

	printf("Parser finished\n");
	return (true);
}
