/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:54:49 by atifany           #+#    #+#             */
/*   Updated: 2022/11/11 20:33:26 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

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
		if (ft_strcmp(str, "\n") != 0 && *str != '#')
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

int	parse_textures(char** file_text)
{
	void*	texture;
	char**	texture_line;

	int i = 0;
	while (file_text[i] != NULL
		&& ft_strcmp(file_text[i], "MAP") != 0)
	{
		texture_line = ft_split(file_text[i], ' ');
		if (charpp_length(texture_line) != 2)
		{
			free_array(texture_line);
			return (ERR_INVALID_FILE_HEAD);
		}
		texture = init_textures(texture_line[1], texture_line[0]);
		if (texture == NULL)
		{
			free_array(texture_line);
			return (ERR_INVALID_TEXTURE_PATH);
		}
		ft_lstadd_back(&(g_mlx->textures),
			ft_lstnew(texture));
		free_array(texture_line);
		i++;
	}
	return (SUCCESS);
}

t_wall* init_wall(char** map_line)
{
	t_wall* wall = ft_calloc(1, sizeof(t_wall));
	wall->v1 = (t_fpoint){ atof(map_line[1]), atof(map_line[2])};
	wall->v2 = (t_fpoint){ atof(map_line[3]), atof(map_line[4])};
	
	t_list* tmp = g_mlx->textures;
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_img *)(tmp->content))->name, map_line[5]))
		{
			wall->texture = tmp->content;
			break ;
		}
		tmp = tmp->next;
	}
	return (wall);
}

void	init_player(char** map_line, t_game_data* g_d)
{
	char* map = "SENW";
	
	g_d->player->position =
		(t_fpoint){ atof(map_line[1]), atof(map_line[2])};
	for (int i = 0; i < 4; i++)
	{
		if (map_line[3][0] == map[i])
			break ;
		g_d->player->view_angle += 90;
	}
}

int parse_map(t_game_data* g_d, char** file_text)
{
	void*	wall;
	char**	map_line;

	int i = 0;
	while (file_text[i] != NULL
		&& ft_strcmp(file_text[i], "MAP") != 0) { i++; }
	i++;
	while (file_text[i] != NULL)
	{
		map_line = ft_split(file_text[i], ':');
		if (charpp_length(map_line) == 6 &&
			ft_strcmp(map_line[0], "Wall") == 0)
		{
			wall = init_wall(map_line);
			ft_lstadd_back(&(g_d->scene),
				ft_lstnew(wall));
			free_array(map_line);
		}
		else if (charpp_length(map_line) == 4 &&
			ft_strcmp(map_line[0], "Player") == 0)
		{
			init_player(map_line, g_d);
		}
		else
		{
			free_array(map_line);
			return (ERR_INVALID_MAP);
		}
		i++;
	}

	return (SUCCESS);
}
