/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:45:54 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 16:54:33 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

void	parse_player(t_game_data *g_d, int x, int y, char dir)
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

int	read_texture(void *_texture, char *split_line)
{
	t_img	**texture;

	texture = (t_img **)_texture;
	if (!split_line)
		return (ERR_INVALID_FILE_HEAD);
	if (!*(texture))
	{
		*(texture) = init_textures(split_line);
		if (*(texture) == NULL)
			return (ERR_INVALID_TEXTURE_PATH);
	}
	return (SUCCESS);
}

int	read_color(void *_color_hex, char *color_line)
{
	int		*color_hex;
	char	**color_rgb;

	color_hex = (int *)_color_hex;
	if (!color_line)
		return (ERR_INVALID_FILE_HEAD);
	color_rgb = ft_split(color_line, ',');
	if (!color_rgb[0] || !color_rgb[1] || !color_rgb[2] || color_rgb[3]
		|| !is_valid_color(color_rgb[0], color_rgb[1], color_rgb[2]))
	{
		free_array(color_rgb);
		return (ERR_INVALID_COLOR);
	}
	*color_hex = (ft_atoi(color_rgb[0]) << 16) + (ft_atoi(color_rgb[1]) << 8)
		+ ft_atoi(color_rgb[2]);
	free_array(color_rgb);
	return (SUCCESS);
}

void	write_line_to_map(char *cut_text, char **map)
{
	int	i;
	int	j;
	int	linelen;

	linelen = ft_strlen(cut_text);
	*map = ft_calloc(MAP_RES * linelen * 8 + 1, sizeof(char));
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
