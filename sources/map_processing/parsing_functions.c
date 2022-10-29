#include "../_headers/cub3d.h"

bool	is_valid_id(char *id)
{
	char	*allowed_ids[6] = {"F", "C", "NO", "WE", "EA", "SO"};
	int		i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(id, allowed_ids[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	parse_colors(int **keywords_map, char **split_line, t_game_data *g_d)
{
	if (ft_strcmp(split_line[0], "F") == 0)
	{
		(*keywords_map)[0]++;
		if (read_color(&(g_d->floor), split_line[1]) == false)
			return (5);
	}
	if (ft_strcmp(split_line[0], "C") == 0)
	{
		(*keywords_map)[1]++;
		if (read_color(&(g_d->ceiling), split_line[1]) == false)
			return (6);
	}
	if ((*keywords_map)[0] > 1 || (*keywords_map)[1] > 1)
		return (7);
	return (-1);
}

int	parse_textures(int **keywords_map, char **split_line, t_game_data *g_d)
{
	if (ft_strcmp(split_line[0], "NO") == 0)
	{
		(*keywords_map)[2]++;
		if (read_texture(&(g_mlx->texture_north), split_line[1], g_d) == false)
			return (10);
	}
	if (ft_strcmp(split_line[0], "SO") == 0)
	{
		(*keywords_map)[3]++;
		if (read_texture(&(g_mlx->texture_south), split_line[1], g_d) == false)
			return (10);
	}
	if (ft_strcmp(split_line[0], "WE") == 0)
	{
		(*keywords_map)[4]++;
		if (read_texture(&(g_mlx->texture_west), split_line[1], g_d) == false)
			return (10);
	}
	if (ft_strcmp(split_line[0], "EA") == 0)
	{
		(*keywords_map)[5]++;
		if (read_texture(&(g_mlx->texture_east), split_line[1], g_d) == false)
			return (10);
	}
	if ((*keywords_map)[2] > 1 || (*keywords_map)[3] > 1
		|| (*keywords_map)[4] > 1 || (*keywords_map)[5] > 1)
		return (7);
	return (-1);
}

int	parse_head(char **file_text, t_game_data *g_d)
{
	int		*keywords_map;
	int		ret;
	char	**split_line;
	int		i;

	keywords_map = ft_calloc(6, sizeof(int));
	i = 0;
	while (file_text[i] && i < 6)
	{
		split_line = ft_split(file_text[i], ' ');
		if (split_line == NULL || !is_valid_id(split_line[0]))
			return (7);
		ret = parse_colors(&keywords_map, split_line, g_d);
		if (ret != -1)
			return (ret);
		ret = parse_textures(&keywords_map, split_line, g_d);
		if (ret != -1)
			return (ret);
		free_array(split_line);
		i++;
	}
	free(keywords_map);
	if (i != 6)
		return (7);
	return (-1);
}

char	**read_file(char *file_path)
{
	int		i;
	int		fd;
	char	*str;
	char	**file_text;

	fd = open(file_path, O_RDONLY, 0777);
	if (fd == -1)
		return (NULL);
	i = 1;
	str = get_next_line(fd);
	file_text = ft_calloc(1, sizeof(char *));
	while (str)
	{
		if (ft_strcmp(str, "\n") != 0)
		{
			file_text = ft_realloc_charpp(file_text, (i + 1) * sizeof(char *),
				i * sizeof(char *));
			file_text[i - 1] = ft_strtrim(str, "\n");
			file_text[i] = NULL;
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (file_text);
}

char	**cut_trailings(char **file_text)
{
	int		leftest_border;
	int		i;
	int		j;
	char	**cut_text;

	cut_text = ft_calloc(1, sizeof(char *));
	leftest_border = INT_MAX;
	j = 1;
	i = -1;
	while ((++i != -1) && file_text[i])
	{
		if (*(file_text[i]) == 0)
			continue ;
		if (find_left_border(file_text[i]) < leftest_border)
			leftest_border = find_left_border(file_text[i]);
		cut_text = ft_realloc_charpp(cut_text, (j + 1) * sizeof(char *),
				j * sizeof(char *));
		cut_text[j - 1] = ft_substr(file_text[i], leftest_border,
				find_right_border(file_text[i]) - leftest_border + 1);
		cut_text[j] = NULL;
		j++;
	}
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
			write_line_to_map(cut_text[i], &(map[i * MAP_RES + j]));
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
// 		// | | This cycle is daaamn slooooow... find a way to speed things up
// 		// V V
// 		while (j < (i + 1) * MAP_RES)
// 			map[j++] = ft_strdup(line_cpy);
// 		free(line_cpy);
// 		i++;
// 	}
// 	return (map);
// }
