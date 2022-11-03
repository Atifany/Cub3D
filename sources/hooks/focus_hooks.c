/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focus_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:00:32 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 22:10:47 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

void	focus_change_button(t_game_data *g_d)
{
	if (g_d->is_focused == true)
		focus_out(g_d);
	else
		focus_in(g_d);
}

#ifdef __APPLE__

int	focus_in(t_game_data *g_d)
{
	mlx_mouse_hide();
	g_d->is_focused = true;
	set_new_mouse_pos(g_d->res.x / 2, g_d->res.y / 2);
	return (0);
}

int	focus_out(t_game_data *g_d)
{
	mlx_mouse_show();
	g_d->is_focused = false;
	return (0);
}

#endif // __APPLE__

#ifdef __linux__

int	focus_in(t_game_data *g_d)
{
	mlx_mouse_hide(g_mlx->mlx, g_mlx->win);
	g_d->is_focused = true;
	set_new_mouse_pos(g_d->res.x / 2, g_d->res.y / 2);
	return (0);
}

int	focus_out(t_game_data *g_d)
{
	mlx_mouse_show(g_mlx->mlx, g_mlx->win);
	g_d->is_focused = false;
	return (0);
}

#endif // __linux__
