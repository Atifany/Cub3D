/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:18 by atifany           #+#    #+#             */
/*   Updated: 2022/11/14 21:53:04 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

int	move_player(t_fpoint shift, t_game_data *g_d)
{
	float		cos_dir;
	float		sin_dir;
	t_fpoint	new_pos;
	int			*ret;

	cos_dir = cos(deg_to_rad(g_d->player->view_angle_h));
	sin_dir = sin(deg_to_rad(g_d->player->view_angle_h));
	new_pos.x = g_d->player->position.x + shift.x * cos_dir + shift.y * sin_dir;
	new_pos.y = g_d->player->position.y + shift.x * sin_dir - shift.y * cos_dir;

	g_d->player->position.x = new_pos.x;
	g_d->player->position.y = new_pos.y;

	return (0);
}

int	rotate_player(float shift_h, float shift_v, t_game_data *g_d)
{
	g_d->player->view_angle_h += shift_h;
	if (g_d->player->view_angle_h <= 0)
		g_d->player->view_angle_h = 360 + g_d->player->view_angle_h;
	else if (g_d->player->view_angle_h > 360)
		g_d->player->view_angle_h = g_d->player->view_angle_h - 360;
	
	if (g_d->player->view_angle_v + shift_v < 0
		|| g_d->player->view_angle_v + shift_v > 180)
		return (0);
	g_d->player->view_angle_v += shift_v;
	return (0);
}
