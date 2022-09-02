
#include "../_headers/cub3d.h"

void	display_charpp(char **arr)
{
	int i = 0;

	if (!arr || !*arr)
		printf("DEBUG: array is empty.\n");
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

static char	**read_file(char *file_path)
{
	int		fd;
	int		i;
	char	**file_text;
	char	*str;

	i = 0;
	file_text = (char **)malloc(1 * sizeof(char *));
	fd = open(file_path, O_RDWR, 0777);
	if (fd < 0)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		file_text[i++] = ft_strdup(str);
		file_text = realloc(file_text, i);
		file_text[i] = NULL;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (file_text);
}

bool	parse_file(t_game_data *g_d, char *file_path)
{
	char	**file_text;

	if (!is_valid_file(file_path))
		return (false);
	file_text = read_file(file_path);
	if (!file_text)
		error_die(g_d, "Cub3D: Error: Cannot open given file.\n", 1);
	//display_charpp(file_text);
	return (true);
}
