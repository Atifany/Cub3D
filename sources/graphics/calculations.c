/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:26:41 by hnickole          #+#    #+#             */
/*   Updated: 2022/10/29 19:35:30 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

double	deg_to_rad(float a)
{
	return (a * M_PI / 180);
}

float	distance(t_point p1, t_fpoint p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

unsigned int	darker(int c, int d)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = c >> 16;
	g = c >> 8;
	b = c;
	if (r > d)
		r -= d;
	else
		r = 0;
	if (g > d)
		g -= d;
	else
		g = 0;
	if (b > d)
		b -= d;
	else
		b = 0;
	return ((r << 16) + (g << 8) + b);
}

static void	init_points(t_fpoint *dir, t_fpoint *pos, t_game_data *gd, int col)
{
	dir->x = (cos(deg_to_rad(gd->player->view_angle - 45
					+ ((float)gd->fov) / ((float)gd->res.x) * ((float)col))));
	dir->y = (sin(deg_to_rad(gd->player->view_angle - 45
					+ ((float)gd->fov) / ((float)gd->res.x) * ((float)col))));
	pos->x = gd->player->position.x;
	pos->y = gd->player->position.y;
}

t_point	cast_ray(t_game_data *gd, int col)
{
	t_fpoint	dir;
	t_fpoint	pos;
	t_point		ret;
	int			i;

	ret.x = -1;
	ret.y = -1;
	i = -1;
	init_points(&dir, &pos, gd, col);
	while (++i < MAP_RES)
	{
		pos.x += dir.x * ((1 << (i >> 8)));
		pos.y += dir.y * ((1 << (i >> 8)));
		if (gd->map[(int)pos.x][(int)pos.y] == '1')
		{
			while (gd->map[(int)pos.x][(int)pos.y] == '1')
			{
				pos.x -= dir.x;
				pos.y -= dir.y;
			}
			ret.x = (int)(pos.x + dir.x);
			ret.y = (int)(pos.y + dir.y);
			return (ret);
		}
	}
	return (ret);
}
