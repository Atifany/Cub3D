
#include "../_headers/cub3d.h"

bool	is_valid_file(char *file_path)
{
	if (ft_strnstr(file_path, ".cub", INT32_MAX)
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