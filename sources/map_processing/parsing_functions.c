/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:54:49 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 17:17:41 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

int	parse_head(char **file_text, t_game_data *g_d)
{
	int			ret;
	int			i;
	char		**split_line;
	t_head_map	*h_map;

	h_map = init_head_map(g_d);
	i = 0;
	while (file_text[i] && i < 6)
	{
		split_line = ft_split(file_text[i], ' ');
		ret = parse_head_line(&h_map, split_line);
		free_array(split_line);
		if (ret != SUCCESS)
		{
			free(h_map);
			return (ret);
		}
		i++;
	}
	free(h_map);
	if (i != 6)
		return (ERR_INVALID_FILE_HEAD);
	return (SUCCESS);
}

char	**read_file(char *file_path)
{
	int		i;
	int		fd;
	char	*str;
	char	**file_text;

	fd = open(file_path, O_RDONLY, 0777);
	if (fd == -1)
		return (NULL);
	i = 1;
	str = get_next_line(fd);
	file_text = ft_calloc(1, sizeof(char *));
	while (str)
	{
		if (ft_strcmp(str, "\n") != 0)
		{
			file_text = ft_realloc_charpp(file_text, (i + 1) * sizeof(char *),
					i * sizeof(char *));
			file_text[i - 1] = ft_strtrim(str, "\n");
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (file_text);
}

char	**cut_trailings(char **file_text)
{
	int		leftest_border;
	int		i;
	int		j;
	char	**cut_text;

	cut_text = ft_calloc(1, sizeof(char *));
	leftest_border = INT_MAX;
	j = 1;
	i = -1;
	while ((++i != -1) && file_text[i])
	{
		if (*(file_text[i]) == 0)
			continue ;
		if (find_left_border(file_text[i]) < leftest_border)
			leftest_border = find_left_border(file_text[i]);
		cut_text = ft_realloc_charpp(cut_text, (j + 1) * sizeof(char *),
				j * sizeof(char *));
		cut_text[j - 1] = ft_substr(file_text[i], leftest_border,
				find_right_border(file_text[i]) - leftest_border + 1);
		j++;
	}
	return (cut_text);
}

void	clean_spaces(t_game_data *g_d, char **cut_text)
{
	int		i;
	int		j;

	i = 0;
	while (cut_text[i])
	{
		j = 0;
		while (cut_text[i][j])
		{
			if (ft_isspace(cut_text[i][j]))
				cut_text[i][j] = '1';
			else if (is_spawner(cut_text[i][j]))
			{
				parse_player(g_d, i, j, cut_text[i][j]);
				cut_text[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

char	**multiply_size(char **cut_text)
{
	int		i;
	int		j;
	char	**map;

	map = (char **)ft_calloc(
			count_items_charpp(cut_text) * MAP_RES + 1, sizeof(char *));
	i = 0;
	while (cut_text[i])
	{
		j = 0;
		while (j < MAP_RES)
		{
			write_line_to_map(cut_text[i], &(map[i * MAP_RES + j]));
			j++;
		}
		i++;
	}
	return (map);
}
