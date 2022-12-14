/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:47:26 by atifany           #+#    #+#             */
/*   Updated: 2022/11/11 20:08:05 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

static int	clean_return(int ret, char **arr)
{
	free_array(arr);
	return (ret);
}

int	parse_file(t_game_data *g_d, char *file_path)
{
	int		ret;
	int		shift_to_map;
	char	**file_text;

	shift_to_map = 6;
	if (is_valid_file(file_path) == false)
		return (ERR_INVALID_FILENAME);
	file_text = read_file(file_path);
	if (file_text == NULL)
		return (ERR_CANNOT_OPEN);

	ret = parse_textures(file_text);
	if (ret != SUCCESS)
		return (ret);
	
	ret = parse_map(g_d, file_text);
	if (ret != SUCCESS)
		return (ret);

	// ret = parse_head(file_text, g_d);
	// if (ret != SUCCESS)
	// 	return (clean_return(ret, file_text));
	
	// if (is_valid_map(file_text + shift_to_map) == false)
	// 	return (clean_return(ERR_INVALID_MAP, file_text));
	// g_d->map = cut_trailings(file_text + shift_to_map);
	// free_array(file_text);
	// clean_spaces(g_d, g_d->map);
	printf("Cub3D: Parser finished\n");
	return (SUCCESS);
}
