/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:46:33 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 14:46:34 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

int	count_items_charpp(char **charpp)
{
	int	i;

	i = 0;
	while (charpp && charpp[i])
		i++;
	return (i);
}

char	*multiply_line(char *line)
{
	int		i;
	int		j;
	char	*extended_line;

	extended_line = (char *)ft_calloc(
			ft_strlen(line) * MAP_RES + 1, sizeof(char));
	i = 0;
	while (line[i])
	{
		j = i * MAP_RES;
		while (j < (i + 1) * MAP_RES)
			extended_line[j++] = line[i];
		i++;
	}
	return (extended_line);
}

bool	is_spawner(char c)
{
	if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
		return (true);
	return (false);
}

int	find_left_border(char *line)
{
	int	ans;

	ans = 0;
	while (line[ans] && ft_isspace(line[ans]))
		ans++;
	return (ans);
}

int	find_right_border(char *line)
{
	int	ans;

	ans = ft_strlen(line) - 1;
	while (line[ans] && ft_isspace(line[ans]))
		ans--;
	return (ans);
}
