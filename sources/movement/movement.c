/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:18 by atifany           #+#    #+#             */
/*   Updated: 2022/11/10 16:12:44 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

static int	check_main_diagonal(t_game_data *g_d,
	t_fpoint new_pos, int i, int j)
{
	int	istart;
	int	jstart;
	int	jend;

	istart = new_pos.x - (g_d->player->size.x / 2);
	jstart = new_pos.y - (g_d->player->size.y / 2);
	jend = new_pos.y + (g_d->player->size.y / 2);
	if (i <= new_pos.x && j - jstart <= i - istart)
		return (0);
	else if (j <= new_pos.y && j - jstart >= i - istart)
		return (1);
	else if (j >= new_pos.y && j + i - istart <= jend - 1)
		return (2);
	else if (i <= new_pos.x && j + i - istart >= jend - 1)
		return (3);
	else if (i >= new_pos.x && j + i - istart <= jend - 1)
		return (4);
	else if (j <= new_pos.y && j + i - istart >= jend - 1)
		return (5);
	else if (j >= new_pos.y && j - jstart <= i - istart)
		return (6);
	else if (i >= new_pos.x && j - jstart >= i - istart)
		return (7);
	return (7);
}

static int	*count_collisions(t_game_data *g_d, t_fpoint new_pos)
{
	int	i;
	int	j;
	int	*ret;

	ret = (int *)ft_calloc(8, sizeof(int));
	i = new_pos.x - (g_d->player->size.x / 2);
	while (i < new_pos.x + (g_d->player->size.x / 2))
	{
		j = new_pos.y - (g_d->player->size.y / 2);
		while (j < new_pos.y + (g_d->player->size.y / 2))
		{
			if (g_d->map[i][j] == '1')
				ret[check_main_diagonal(g_d, new_pos, i, j)]++;
			j++;
		}
		i++;
	}
	return (ret);
}

static int	*is_collision(t_game_data *g_d, t_fpoint new_pos)
{
	int	*collisions;
	int	*count;

	count = count_collisions(g_d, new_pos);
	collisions = (int *)ft_calloc(4, sizeof(int));
	collisions[NORTH] = ((count[1] >= count[0] && count[1])
			|| (count[2] >= count[3] && count[2]));
	collisions[EAST] = ((count[3] >= count[2] && count[3])
			|| (count[7] >= count[6] && count[7]));
	collisions[SOUTH] = ((count[5] >= count[4] && count[5])
			|| (count[6] >= count[7] && count[6]));
	collisions[WEST] = ((count[0] >= count[1] && count[0])
			|| (count[4] >= count[5] && count[4]));
	free(count);
	return (collisions);
}

int	move_player(t_fpoint shift, t_game_data *g_d)
{
	float		cos_dir;
	float		sin_dir;
	t_fpoint	new_pos;
	int			*ret;

	cos_dir = cos(deg_to_rad(g_d->player->view_angle));
	sin_dir = sin(deg_to_rad(g_d->player->view_angle));
	new_pos.x = g_d->player->position.x + shift.x * cos_dir + shift.y * sin_dir;
	new_pos.y = g_d->player->position.y + shift.x * sin_dir - shift.y * cos_dir;
	// ret = is_collision(g_d, new_pos);
	// if ((!ret[NORTH] && new_pos.x < g_d->player->position.x)
	// 	|| (!ret[SOUTH] && new_pos.x >= g_d->player->position.x))
		g_d->player->position.x = new_pos.x;
	// if ((!ret[WEST] && new_pos.y < g_d->player->position.y)
	// 	|| (!ret[EAST] && new_pos.y >= g_d->player->position.y))
		g_d->player->position.y = new_pos.y;
	// free(ret);
	return (0);
}

int	rotate_player(float shift, t_game_data *g_d)
{
	g_d->player->view_angle += shift;
	if (g_d->player->view_angle <= 0)
		g_d->player->view_angle = 360 + g_d->player->view_angle;
	else if (g_d->player->view_angle > 360)
		g_d->player->view_angle = g_d->player->view_angle - 360;
	return (0);
}
