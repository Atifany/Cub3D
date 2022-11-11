/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:18 by atifany           #+#    #+#             */
/*   Updated: 2022/11/11 19:35:26 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

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

	g_d->player->position.x = new_pos.x;
	g_d->player->position.y = new_pos.y;

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
