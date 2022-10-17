#include "../_headers/cub3d.h"

bool	parse_file(t_game_data *g_d, char *file_path)
{
	int		shift;
	char	**file_text;
	char	**cut_text;

	if (!is_valid_file(file_path))
		return (false);
	file_text = read_file(file_path);
	if (!file_text)
		error_die(g_d, "Cub3D: Error: Cannot open given file.\n", 1);
	shift = parse_head(file_text, g_d);
	if (!is_valid_map(file_text + shift))
		error_die(g_d, "Cub3D: Error: Invalid map.\n", 1);
	cut_text = cut_trailings(file_text + shift);
	free_array(file_text);
	clean_spaces(g_d, cut_text);
	g_d->map = multiply_size(cut_text);
	free_array(cut_text);
	printf("Parser finished\n");
	return (true);
}
