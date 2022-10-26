#include "../_headers/cub3d.h"

int	parse_file(t_game_data *g_d, char *file_path)
{
	int		ret;
	int		shift_to_map;
	char	**file_text;
	char	**cut_text;

	shift_to_map = 6;
	if (!is_valid_file(file_path))
		return (2);
	file_text = read_file(file_path);
	if (!file_text)
		return (3);
	ret = parse_head(file_text, g_d);
	if (ret >= 0)
		return (ret);
	if (!is_valid_map(file_text + shift_to_map))
		return (4);
	cut_text = cut_trailings(file_text + shift_to_map);
	free_array(file_text);
	clean_spaces(g_d, cut_text);
	display_charpp(cut_text);
	g_d->map = multiply_size(cut_text);
	free_array(cut_text);
	//printf("Parser finished\n");
	return (-1);
}
