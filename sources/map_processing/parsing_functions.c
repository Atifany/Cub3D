#include "../_headers/cub3d.h"

int	parse_head(char **file_text, t_game_data *g_d)
{
	char	**color;
	char	**split_line;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (file_text[i] && count < 6)
	{
		split_line = ft_split(file_text[i], ' ');
		if (!ft_strcmp(split_line[0], "NO") && ++count)
			g_mlx->texture_north = init_textures(ft_strtrim(split_line[1], "\n"), g_d);
		else if (!ft_strcmp(split_line[0], "SO") && ++count)
			g_mlx->texture_south = init_textures(ft_strtrim(split_line[1], "\n"), g_d);
		else if (!ft_strcmp(split_line[0], "EA") && ++count)
			g_mlx->texture_east = init_textures(ft_strtrim(split_line[1], "\n"), g_d);
		else if (!ft_strcmp(split_line[0], "WE") && ++count)
			g_mlx->texture_west = init_textures(ft_strtrim(split_line[1], "\n"), g_d);
		else if (!ft_strcmp(split_line[0], "F") && ++count)
		{
			color = ft_split(split_line[1], ',');
			g_d->floor = (ft_atoi(color[0]) << 16) + (ft_atoi(color[1]) << 8) + ft_atoi(color[2]);
			free_array(color);
		}
		else if (!ft_strcmp(split_line[0], "C") && ++count)
		{
			color = ft_split(split_line[1], ',');
			g_d->ceiling = (ft_atoi(color[0]) << 16) + (ft_atoi(color[1]) << 8) + ft_atoi(color[2]);
			free_array(color);
		}
		else if (!ft_strcmp(split_line[0], "\n"))
			(void)g_d;
		else
		{
			free_array(split_line);
			error_die(g_d, "Cub3D: Error: File's head is corrupted.\n", 0);
		}
		free_array(split_line);
		i++;
	}
	if (count != 6)
		error_die(g_d, "Cub3D: Error: File's head is corrupted.\n", 0);
	return (i);
}

char	**read_file(char *file_path)
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

char	**cut_trailings(char **file_text)
{
	int		leftest_border;
	int		i;
	int		j;
	char	**cut_text;

	leftest_border = INT_MAX;
	j = 0;
	i = 0;
	while (file_text[i])
	{
		if (find_left_border(file_text[i]) < leftest_border)
			leftest_border = find_left_border(file_text[i]);
		if (*(file_text[i]) != '\n')
			j++;
		i++;
	}
	cut_text = (char **)ft_calloc(j + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (file_text[i])
	{
		if (*(file_text[i]) != '\n')
		{
			cut_text[j] = ft_substr(file_text[i],
				leftest_border,
				find_right_border(file_text[i]) - leftest_border + 1);
			j++;
		}
		i++;
	}
	cut_text[j] = NULL;
	return (cut_text);
}

void	clean_spaces(t_game_data *g_d, char **cut_text)
{
	int		i;
	int		j;

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
				parse_player_transform(g_d, i, j, cut_text[i][j]);
				cut_text[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	write_line_to_map(char *cut_text, char **map)
{
	int	i;
	int	j;
	int	linelen;

	linelen = ft_strlen(cut_text);
	*map = malloc(MAP_RES*linelen*8); 
	i = 0;
	while (cut_text[i])
	{
		j = 0;
		while (j < MAP_RES)
		{
			(*map)[i*MAP_RES + j] = cut_text[i];
			j++;
		}
		i++;
	}
}

char	**multiply_size(char **cut_text)
{
	int		i;
	int		j;
	char	**map;

	map = (char **)ft_calloc(
			count_items_charpp(cut_text) * MAP_RES + 1, sizeof(char *));
	i = 0;
	while (cut_text[i])
	{
		j = 0;
		while (j < MAP_RES)
		{
			write_line_to_map(cut_text[i], &(map[i*MAP_RES+j]));
			j++;
		}
		i++;
	}
	return (map);
}

// char	**multiply_size(char **cut_text)
// {
// 	int		j;
// 	int		i;
// 	char	*line_cpy;
// 	char	**map;
//
// 	map = (char **)ft_calloc(
// 			count_items_charpp(cut_text) * MAP_RES + 1, sizeof(char *));
// 	i = 0;
// 	while (cut_text[i])
// 	{
// 		line_cpy = multiply_line(cut_text[i]);
// 		j = i * MAP_RES;
// 		// | |		This cycle is daaamn slooooow... find a way to speed things up
// 		// V V
// 		while (j < (i + 1) * MAP_RES)
// 			map[j++] = ft_strdup(line_cpy);
// 		free(line_cpy);
// 		i++;
// 	}
// 	return (map);
// }
