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

bool	read_textures(int *count, char **split_line, t_game_data *g_d)
{
	if (!*split_line)
		return (false);
	if (!ft_strcmp(split_line[0], "NO") && !(g_mlx->texture_north) && ++*count)
		g_mlx->texture_north = init_textures(split_line[1], g_d);
	else if (!ft_strcmp(split_line[0], "SO") && !(g_mlx->texture_south) && ++*count)
		g_mlx->texture_south = init_textures(split_line[1], g_d);
	else if (!ft_strcmp(split_line[0], "EA") && !(g_mlx->texture_east) && ++*count)
		g_mlx->texture_east = init_textures(split_line[1], g_d);
	else if (!ft_strcmp(split_line[0], "WE") && !(g_mlx->texture_west) && ++*count)
		g_mlx->texture_west = init_textures(split_line[1], g_d);
	else
		return (false);
	return (true);
}

bool	read_color(int *count, char **split_line, t_game_data *g_d)
{
	char	**color;

	if (!*split_line)
		return (false);
	if (!ft_strcmp(split_line[0], "F") && ++*count)
	{
		color = ft_split(split_line[1], ',');
		if (!color[0] || !color[1] || !color[2] || color[3]
			|| !is_valid_color(color[0], color[1], color[2]))
		{
			free_array(color);
			error_die(g_d, "Cub3D: Error: Wrong floor color.\n", 0);
		}
		g_d->floor = (ft_atoi(color[0]) << 16) + (ft_atoi(color[1]) << 8)
			+ ft_atoi(color[2]);
		free_array(color);
	}
	else if (!ft_strcmp(split_line[0], "C") && ++*count)
	{
		color = ft_split(split_line[1], ',');
		if (!color[0] || !color[1] || !color[2] || color[3]
			|| !is_valid_color(color[0], color[1], color[2]))
		{
			free_array(color);
			error_die(g_d, "Cub3D: Error: Wrong floor color.\n", 0);
		}
		g_d->ceiling = (ft_atoi(color[0]) << 16) + (ft_atoi(color[1]) << 8)
			+ ft_atoi(color[2]);
		free_array(color);
	}
	else
		return (false);
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
