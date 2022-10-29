/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hnickole <hnickole@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/29 14:42:13 by hnickole		  #+#	#+#			 */
/*   Updated: 2022/10/29 14:48:50 by hnickole		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../_headers/cub3d.h"

static void	draw_line(int col, t_point collision, t_game_data *gd, t_img *texture)
{
	float			d;
	int				ag[5];
	unsigned int	t_pixel;

	ag[3] = (collision.x + collision.y) / 2 % 128;
	ag[1] = 0;
	d = distance(collision, (gd->player->position)) * 64 / MAP_RES;
	if ((d < 256))
	{
		ag[2] = (gd->res.y * 16) / d;
		ag[0] = 0;
		if (d >= 16)
			ag[0] = (gd->res.y - ag[2]) >> 1;
		else
			ag[1] = (ag[2] - gd->res.y) >> 1;
		while (ag[1] < ag[2] && ag[0] < gd->res.y)
		{
			ag[4] = ag[2] >> 8;
			t_pixel = darker(my_pixel_get(texture, ag[3],
						((ag[1] << 7) / ag[2]) % 128), d);
			while (ag[4]-- >= 0 && ag[0] < gd->res.y && ag[1]++ + 1)
				my_pixel_put(g_mlx->img, col, ag[0]++, t_pixel);
		}
	}
}

void	draw_map(t_game_data *gd)
{
	int	i;
	int	ag[4];

	i = 0;
	my_pixel_put(g_mlx->img, gd->player->position.y / (MAP_RES / 8),
		gd->player->position.x / (MAP_RES / 8), 0x00800000);
	while (gd->map[i])
	{
		ag[4] = 0;
		while (gd->map[i][ag[4]])
		{
			if (gd->map[i][ag[4]] == '1')
				my_pixel_put(g_mlx->img, ag[4] / (MAP_RES / 8),
					i / (MAP_RES / 8), 0x00ff0000);
			ag[4] += MAP_RES / 8;
		}
		i += MAP_RES / 8;
	}
}

void	draw_frame(t_game_data *gd)
{
	int		i;
	t_point	collision;
	t_img	*texture;

	g_mlx->img->img = mlx_new_image(g_mlx->mlx, gd->res.x, gd->res.y);
	g_mlx->img->addr = mlx_get_data_addr(g_mlx->img->img, &g_mlx->img->bpp,
			&g_mlx->img->line_length, &g_mlx->img->endian);
	ft_memcpy(g_mlx->img->addr, g_mlx->bg->addr, gd->res.x
		* gd->res.y * (g_mlx->img->bpp / 8));
	i = -1;
	while (++i < gd->res.x)
	{
		collision = cast_ray(gd, gd->res.x - i);
		if (collision.x >= 0)
		{
			if (gd->map[collision.x][collision.y + 1] == '0')
				texture = g_mlx->texture_north;
			else if (gd->map[collision.x + 1][collision.y] == '0')
				texture = g_mlx->texture_west;
			else if (gd->map[collision.x][collision.y - 1] == '0')
				texture = g_mlx->texture_east;
			else
				texture = g_mlx->texture_south;
			draw_line(i, collision, gd, texture);
		}
	}
	draw_map(gd);
}
