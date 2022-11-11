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

int map_multi = 10;

float	distance_between_two_points(t_fpoint p1, t_fpoint p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

void	draw_map(t_game_data *gd)
{
	int	i;
	int	j;

	i = 0;
	while (gd->map[i])
	{
		j = 0;
		while (gd->map[i][j])
		{
			if (gd->map[i][j] == '1')
			{
				for (int m = i * map_multi; m < (i + 1) * map_multi; m++)
				{
					for (int n = j * map_multi; n < (j + 1) * map_multi; n++)
					{
						my_pixel_put(g_mlx->img, n, m, 0x880000);
					}
				}
			}
			j++;
		}
		i++;
	}
	my_pixel_put(g_mlx->img, gd->player->position.y * map_multi,
		gd->player->position.x * map_multi, 0xFFFFFFFF);
}

t_fpoint is_intersect_segments(t_fpoint p1, t_fpoint p2, t_fpoint p3, t_fpoint p4)
{
	const float d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / d;
	const float u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x)) / d;
	if (!(0 < u && u < 1 && t > 0))
		return ((t_fpoint){-1.0f, -1.0f});
	return ((t_fpoint){p3.x + u * (p4.x - p3.x), p3.y + u * (p4.y - p3.y)});
}

t_fpoint run_block(t_game_data *gd, t_fpoint dir, int x, int y)
{
	t_fpoint collision;
	int rot[4][4] = {{0, 0, 1, 0},
					 {1, 0, 1, 1},
					 {1, 1, 0, 1},
					 {0, 1, 0, 0}};
	float buf_dist = -1.0f;
	float record_dist = INT_MAX;
	t_fpoint record_col = {-1.0f, -1.0f};
	
	for (int i = 0; i < 4; i++)
	{
		collision = is_intersect_segments(
		gd->player->position,
		(t_fpoint){dir.x, dir.y},
		(t_fpoint){x + rot[i][0], y + rot[i][1]}, (t_fpoint){x + rot[i][2], y + rot[i][3]});
		if (collision.x <= 0.0f)
			continue;
		buf_dist = distance_between_two_points(gd->player->position, collision);
		if (buf_dist < record_dist)
		{
			record_dist = buf_dist;
			record_col = collision;
		}
	}
	return (record_col);
}

static t_fpoint cast_ray(t_game_data *gd, int col, float* dist)
{
	const t_fpoint dir = {
		gd->player->position.x + cos(deg_to_rad(
			gd->player->view_angle - (float)(gd->fov / 2)
				+ (((float)(gd->fov) / (float)(gd->res.x)) * (float)(col)))),
		gd->player->position.y + sin(deg_to_rad(
			gd->player->view_angle - (float)(gd->fov / 2)
				+ (((float)(gd->fov) / (float)(gd->res.x)) * (float)(col))))};
	
	t_fpoint collision;
	float buf_dist = -1.0f;
	t_fpoint record_col = {-1.0f, -1.0f};

	int i = 0;
	int j = 0;
	while (gd->map[i] != NULL)
	{
		j = 0;
		while (gd->map[i][j] != 0)
		{
			if (gd->map[i][j] == '1')
			{
				collision = run_block(gd, dir, i, j);
				buf_dist = distance_between_two_points(gd->player->position, collision);
				if (buf_dist < *dist)
				{
					*dist = buf_dist;
					record_col = collision;
				}
			}
			j++;
		}
		i++;
	}
	return (record_col);
	// if (record_col.x >= 0.0f)
	//	 my_pixel_put(g_mlx->img, record_col.y * map_multi, record_col.x * map_multi, 0x00FF00);
}

void	draw_line(t_game_data *gd, t_fpoint collision, float dist, int col)
{
	const float dist_to_full_screen = 0.5f;

	int height = gd->res.y * (dist_to_full_screen / dist);
	int px_start = 0 + (gd->res.y - height) / 2;
	int px_end = gd->res.y - (gd->res.y - height) / 2;
	// kostil:
	if (px_start < 0)
		px_start = 0;
	if (px_start > gd->res.y)
		px_start = gd->res.y;
	if (px_end < 0)
		px_end = 0;
	if (px_end > gd->res.y)
		px_end = gd->res.y;

	for (int i = px_start; i < px_end; i++)
	{
		if (0 > i && i > gd->res.y)
			continue ;
		//printf("x=%d y=%d\n", i, col);
		my_pixel_put(g_mlx->img, gd->res.x - col, i, 0xAAAAAA);
	}
}

void	draw_frame(t_game_data *gd)
{
	float		dist;
	t_fpoint	collision;
	t_img		*texture;

	g_mlx->img->img = mlx_new_image(g_mlx->mlx, gd->res.x, gd->res.y);
	g_mlx->img->addr = mlx_get_data_addr(g_mlx->img->img, &g_mlx->img->bpp,
			&g_mlx->img->line_length, &g_mlx->img->endian);
	ft_memcpy(g_mlx->img->addr, g_mlx->bg->addr, gd->res.x
		* gd->res.y * (g_mlx->img->bpp / 8));
	draw_map(gd);
	for (int i = 0; i < gd->res.x; i++)
	{
		dist = INT_MAX;
		collision = cast_ray(gd, i, &dist);
		if (collision.x < 0.0f)
			continue ;
		draw_line(gd, collision, dist, i);
	}
}
