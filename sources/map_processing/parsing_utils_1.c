#include "../_headers/cub3d.h"

void	parse_player_transform(t_game_data *g_d, int x, int y, char dir)
{
	t_fpoint	position;
	int			view_angle;

	view_angle = 180;
	position.x = (x + 1) * MAP_RES - MAP_RES / 2;
	position.y = (y + 1) * MAP_RES - MAP_RES / 2;
	if (dir == 'W')
		view_angle = 270;
	else if (dir == 'E')
		view_angle = 90;
	else if (dir == 'S')
		view_angle = 0;
	set_player_transform(g_d, position, view_angle);
}

bool	is_valid_color(char *r, char *g, char *b)
{
	int	i;

	if (!r || !*r || !g || !*g || !b || !*b)
		return (false);
	if (ft_strlen(r) > 3 || ft_strlen(g) > 3 || ft_strlen(b) > 3)
		return (false);
	i = 0;
	while (r[i])
		if (!ft_isdigit(r[i++]))
			return (false);
	i = 0;
	while (g[i])
		if (!ft_isdigit(g[i++]))
			return (false);
	i = 0;
	while (b[i])
		if (!ft_isdigit(b[i++]))
			return (false);
	if (ft_atoi(r) > 255 || ft_atoi(r) < 0
		|| ft_atoi(g) > 255 || ft_atoi(g) < 0
		|| ft_atoi(b) > 255 || ft_atoi(b) < 0)
		return (false);
	return (true);
}

bool	read_texture(t_img **texture, char *split_line, t_game_data *g_d)
{
	if (!split_line)
		return (false);
	if (!*(texture))
	{
		*(texture) = init_textures(split_line);
		if (*(texture) == NULL)
			return (false);
	}
	return (true);
}

bool	read_color(int *color_hex, char *color_line)
{
	char	**color_rgb;

	if (!color_line)
		return (false);
	color_rgb = ft_split(color_line, ',');
	if (!color_rgb[0] || !color_rgb[1] || !color_rgb[2] || color_rgb[3]
		|| !is_valid_color(color_rgb[0], color_rgb[1], color_rgb[2]))
	{
		free_array(color_rgb);
		return (false);
	}
	*color_hex = (ft_atoi(color_rgb[0]) << 16) + (ft_atoi(color_rgb[1]) << 8)
			+ ft_atoi(color_rgb[2]);
	free_array(color_rgb);
	return (true);
}

void	write_line_to_map(char *cut_text, char **map)
{
	int	i;
	int	j;
	int	linelen;

	linelen = ft_strlen(cut_text);
	*map = malloc(MAP_RES * linelen * 8);
	i = 0;
	while (cut_text[i])
	{
		j = 0;
		while (j < MAP_RES)
		{
			(*map)[i * MAP_RES + j] = cut_text[i];
			j++;
		}
		i++;
	}
}
