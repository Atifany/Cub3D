/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:57:01 by atifany           #+#    #+#             */
/*   Updated: 2022/11/11 20:36:23 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

static long long	cur_time(long long timestart)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	if (!timestart)
		return (milliseconds);
	return (milliseconds - timestart);
}

static void	display_fps(t_game_data *g_d)
{	
	static int			oldfps = 0;
	static int			fps = 0;
	static long long	secs = 0;
	static long long	timestart = 0;
	char				*string_to_display;

	if (!timestart)
		timestart = cur_time(0);
	fps++;
	if (cur_time(timestart) / 1000 > secs / 1000)
	{
		oldfps = fps;
		fps = 0;
	}
	string_to_display = ft_itoa(oldfps);
	mlx_string_put(g_mlx->mlx, g_mlx->win,
		g_d->res.x - 100, 50,
		0x00FFFFFF, string_to_display);
	free(string_to_display);
	secs = cur_time(timestart);
}

void	update(t_game_data *g_d)
{
	static long long	lastframe = 0;

	if (cur_time(lastframe) > 30)
	{
		lastframe = cur_time(0);
		list_active_keys(g_d);
		draw_frame(g_d);
		mlx_put_image_to_window(g_mlx->mlx, g_mlx->win, g_mlx->img->img, 0, 0);
		display_fps(g_d);
		mlx_destroy_image(g_mlx->mlx, g_mlx->img->img);
	}
}

int	loop_hook(t_game_data *g_d)
{
	update(g_d);
	return (0);
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, KEYPRESS_EXIT_CROSS, 0);
	return (0);
}
