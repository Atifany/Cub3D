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
	int	k;
	int	m;

	if (!ft_strchr(MAP_ALLOWED_LIST, file_text[i][j]))
		return (false);
	if (file_text[i][j] == '0' || is_spawner(file_text[i][j]))
	{
		k = i - 1;
		while (k <= i + 1)
		{
			if ((k < 0 || !file_text[k] || ft_strlen(file_text[k]) <= j + 1) || j == 0)
				return (false);
			m = j - 1;
			while (m <= j + 1)
			{
				if (ft_isspace(file_text[k][m]))
					return (false);
				m++;
			}
			k++;
		}
	}
	return (true);
}

bool	is_valid_map(char **file_text)
{
	int		first_line_index;
	int		i;
	int		j;
	bool	has_spawner;

	first_line_index = 0;
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
