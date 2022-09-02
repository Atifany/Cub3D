
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

static int	usefull_len(char *line)
{
	int len;

	len = (int)ft_strlen(line) - 1;
	while (ft_isspace(line[len]))
		len--;
	return (len + 1);
}

static char	**multiply_by_64(char **cut_text)
{
	int		j;
	int		i;
	int		rows;
	char	**map;

	rows = 0;
	while (cut_text[rows])
		rows++;
	map = (char **)ft_calloc((rows + 1) * TILE_SPLIT, sizeof(char *));
	i = 0;
	while (i < rows * TILE_SPLIT)
	{
		map[i] = (char *)ft_calloc(
			ft_strlen(cut_text[i/TILE_SPLIT]) * TILE_SPLIT, sizeof(char));
		j = 0;
		while (j < (int)ft_strlen(cut_text[i/TILE_SPLIT]) * TILE_SPLIT)
		{
			//if (cut_text[i/TILE_SPLIT][j/TILE_SPLIT] == 'N')
			//{
				//if (i % TILE_SPLIT == TILE_SPLIT/2 && j % TILE_SPLIT == TILE_SPLIT/2)
					map[i][j] = cut_text[i/TILE_SPLIT][j/TILE_SPLIT] - 48;
				//else
				//	map[i][j] = '0';
			//}
			//else
			//	map[i][j] = cut_text[i/TILE_SPLIT][j/TILE_SPLIT];
			j++;
		}
		i++;
	}
	return (map);
}

static char	**cut_trailings(char **file_text)
{
	char	**cut_text;
	int		max_row_length;
	int		i;
	int		j;

	max_row_length = 0;
	i = 0;
	while (file_text[i])
	{
		j = usefull_len(file_text[i]);
		if (j > max_row_length)
			max_row_length = j;
		i++;
	}
	cut_text = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (file_text[i])
	{
		j = 0;
		cut_text[i] = ft_calloc(max_row_length + 1, sizeof(char));
		while (j < max_row_length)
		{
			if (j <= (int)ft_strlen(file_text[i]) - 1 && !ft_isspace(file_text[i][j]))
				cut_text[i][j] = file_text[i][j];
			else
				cut_text[i][j] = '0';
			j++;
		}
		i++;
	}
	return (cut_text);
}

static char	**read_file(char *file_path)
{
	int		fd;
	int		i;
	char	**file_text;
	char	*str;
	int		rows;

	rows = 0;
	fd = open(file_path, O_RDWR, 0777);
	if (fd < 0)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		rows++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	file_text = (char **)ft_calloc(rows + 1, sizeof(char *));
	fd = open(file_path, O_RDWR, 0777);
	if (fd < 0)
		return (NULL);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		file_text[i] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	file_text[i] = NULL;
	close(fd);
	return (file_text);
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
	// is_valid(file_text);
	printf("Raw:\n");
	display_charpp(file_text);
	cut_text = cut_trailings(file_text);
	printf("Cut:\n");
	display_charpp(cut_text);
	g_d->map = multiply_by_64(cut_text);
	printf("Ready to use:\n");
	//display_charpp(g_d->map);
	return (true);
}
