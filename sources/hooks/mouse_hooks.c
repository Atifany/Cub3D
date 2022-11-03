/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:05:42 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 22:23:44 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

int	mouse_move(int x, int y, t_game_data *g_d)
{
	(void)y;
	if (!g_d->is_focused)
		return (0);
	if (x != g_d->res.x / 2)
	{
		rotate_player(((g_d->res.x / 2) - x) * (g_d->player_rot_speed), g_d);
		set_new_mouse_pos(g_d->res.x / 2, g_d->res.y / 2);
	}
	return (0);
}

#ifdef __APPLE__

void	set_new_mouse_pos(int x, int y)
{
	mlx_mouse_move(g_mlx->win, x, y);
}

void	get_mouse_pos(int *mousex, int *mousey)
{
	mlx_mouse_get_pos(g_mlx->win, mousex, mousey);
}

#endif // __APPLE__

#ifdef __linux__

void	set_new_mouse_pos(int x, int y)
{
	mlx_mouse_move(g_mlx->mlx, g_mlx->win, x, y);
}

void	get_mouse_pos(int *mousex, int *mousey)
{
	mlx_mouse_get_pos(g_mlx->mlx, g_mlx->win, mousex, mousey);
}

#endif // __linux__