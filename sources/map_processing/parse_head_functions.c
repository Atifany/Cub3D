/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_head_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:13:32 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 17:13:33 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

t_head_map	*init_head_map(t_game_data *g_d)
{
	t_head_map	*h_map;

	h_map = ft_calloc(7, sizeof(t_head_map));
	h_map[0].id = "NO";
	h_map[0].read_f = &read_texture;
	h_map[0].obj = &(g_mlx->texture_north);
	h_map[1].id = "EA";
	h_map[1].read_f = &read_texture;
	h_map[1].obj = &(g_mlx->texture_east);
	h_map[2].id = "WE";
	h_map[2].read_f = &read_texture;
	h_map[2].obj = &(g_mlx->texture_west);
	h_map[3].id = "SO";
	h_map[3].read_f = &read_texture;
	h_map[3].obj = &(g_mlx->texture_south);
	h_map[4].id = "F";
	h_map[4].read_f = &read_color;
	h_map[4].obj = &(g_d->floor);
	h_map[5].id = "C";
	h_map[5].read_f = &read_color;
	h_map[5].obj = &(g_d->ceiling);
	return (h_map);
}

int	parse_head_line(t_head_map **h_map, char **split_line)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp((*h_map)[i].id, split_line[0]) == 0)
		{
			if ((*h_map)[i].is_found == true)
				return (ERR_INVALID_FILE_HEAD);
			(*h_map)[i].is_found = true;
			return ((*h_map)[i].read_f((*h_map)[i].obj, split_line[1]));
		}
		i++;
	}
	return (ERR_INVALID_FILE_HEAD);
}
