#include "../_headers/cub3d.h"

bool	is_valid_file(char *file_path)
{
	if (ft_strnstr(file_path, ".cub", INT_MAX)
		!= (int)ft_strlen(file_path) - (int)ft_strlen(".cub"))
		return (false);
	return (true);
}

bool	is_valid_input(int argc)
{
	if (argc != 2)
		return (false);
	return (true);
}

static bool	is_valid_tile(char **file_text, int i, int j)
{
	if (!ft_strchr(MAP_ALLOWED_LIST, file_text[i][j]))
		return (false);
	if (file_text[i][j] == '0' || is_spawner(file_text[i][j]))
	{
		if (i == 0 || j == 0
			|| file_text[i + 1] == 0 || file_text[i][j + 1] == 0)
			return (false);
		if (ft_isspace(file_text[i - 1][j])
			|| ft_isspace(file_text[i + 1][j])
			|| ft_isspace(file_text[i][j - 1])
			|| ft_isspace(file_text[i][j + 1]))
			return (false);
	}
	return (true);
}

bool	is_valid_map(char **file_text)
{
	int		i;
	int		j;
	bool	has_spawner;

	has_spawner = false;
	i = 0;
	while (file_text[i])
	{
		j = 0;
		while (file_text[i][j])
		{
			if (!is_valid_tile(file_text, i, j))
				return (false);
			if (is_spawner(file_text[i][j]) && has_spawner)
				return (false);
			if (is_spawner(file_text[i][j]))
				has_spawner = true;
			j++;
		}
		i++;
	}
	return (has_spawner);
}
