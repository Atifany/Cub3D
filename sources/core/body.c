/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:38:45 by atifany           #+#    #+#             */
/*   Updated: 2022/11/10 18:13:10 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

t_mlx_data	*g_mlx;

int	body(t_game_data *g_d)
{
	mlx_do_key_autorepeatoff(g_mlx->mlx);
	set_new_mouse_pos(g_d->res.x / 2, g_d->res.y / 2);
	mlx_mouse_hide(g_mlx->mlx, g_mlx->win);
	mlx_hook(g_mlx->win, DestroyNotify, NoEventMask, die_hook, g_d);
	mlx_hook(g_mlx->win, KeyPress, KeyPressMask, key_down_hook,
		g_d);
	mlx_hook(g_mlx->win, KeyRelease, KeyReleaseMask, key_up_hook,
		&(g_d->keys_pressed));
	mlx_hook(g_mlx->win, FocusIn, FocusChangeMask, focus_in, g_d);
	mlx_hook(g_mlx->win, FocusOut, FocusChangeMask, focus_out, g_d);
	// delete later
	draw_frame(g_d);
	mlx_put_image_to_window(g_mlx->mlx, g_mlx->win, g_mlx->img->img, 0, 0);
	// ^^^^^^^^^^^^
	mlx_loop_hook(g_mlx->mlx, loop_hook, g_d);
	mlx_loop(g_mlx->mlx);
	return (0);
}

int	input_start(int argc, char **argv)
{
	t_game_data	*g_d;
	int			parse_ret;

	printf("Cub3D: Started.\n");
	g_d = ft_calloc(1, sizeof(t_game_data));
	init_g_d_defaults(g_d);
	if (init_window(g_d))
		error_die(g_d, 0, 1);
	if (argc != 2)
		error_die(g_d, 1, 1);
	parse_ret = parse_file(g_d, argv[1]);
	if (parse_ret >= 0)
		error_die(g_d, parse_ret, 1);
	g_mlx->bg = create_background(g_d);
	return (body(g_d));
}
