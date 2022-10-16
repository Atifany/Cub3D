#include "../_headers/cub3d.h"

int	parse_head(char **file_text, t_game_data *g_d)
{
	char	**split_line;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (file_text[i] && count < 6)
	{
		split_line = ft_split(file_text[i], ' ');
		if (++i && read_textures(&count, split_line, g_d))
			free_array(split_line);
		else if (read_color(&count, split_line, g_d)
			|| !ft_strcmp(split_line[0], "\n"))
			free_array(split_line);
		else
		{
			free_array(split_line);
			error_die(g_d, "Cub3D: Error: File's head is corrupted.\n", 0);
		}
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
	i = 1;
	str = get_next_line(fd);
	file_text = ft_calloc(1, sizeof(char *));
	while (str)
	{
		file_text = ft_realloc_charpp(file_text, (i + 1) * sizeof(char *),
				i * sizeof(char *));
		file_text[i - 1] = ft_strdup(str);
		file_text[i] = NULL;
		free(str);
		str = get_next_line(fd);
		i++;
	}
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
		if (*(file_text[i]) == '\n')
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
