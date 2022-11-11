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

float	shift = 0.0f;
int		map_multi = 10;

float	distance_between_two_points(t_fpoint p1, t_fpoint p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

void	draw_line(t_fpoint p1, t_fpoint p2)
{
	t_fpoint	delta;
	t_fpoint	sign;
	t_fpoint	cur;
	int		error[2];

	delta.x = abs(p2.x - p1.x);
	delta.y = abs(p2.y - p1.y);
	sign.x = p1.x < p2.x ? 1 : -1;
	sign.y = p1.y < p2.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = p1;
	while (cur.x != p2.x || cur.y != p2.y)
	{
		my_pixel_put(g_mlx->img, cur.x, cur.y, 0xFF0000);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void	draw_map(t_game_data *gd)
{
	t_list* tmp = gd->scene;

	while (tmp != NULL)
	{
		draw_line(
			(t_fpoint){
				((t_wall *)(tmp->content))->v1.x * map_multi,
				((t_wall *)(tmp->content))->v1.y * map_multi},
			(t_fpoint){
				((t_wall *)(tmp->content))->v2.x * map_multi,
				((t_wall *)(tmp->content))->v2.y * map_multi});
		tmp = tmp->next;
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
	shift = u;
	return ((t_fpoint){p3.x + u * (p4.x - p3.x), p3.y + u * (p4.y - p3.y)});
}

t_fpoint run_block(t_game_data *gd, t_fpoint dir, t_wall* wall)
{
	t_fpoint collision;
	float buf_dist = -1.0f;
	float record_dist = INT_MAX;
	t_fpoint record_col = {-1.0f, -1.0f};

	for (int i = 0; i < 4; i++)
	{
		collision = is_intersect_segments(
			gd->player->position,
			(t_fpoint){dir.x, dir.y}, wall->v1, wall->v2);
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

	t_list* tmp = gd->scene;
	while (tmp != NULL)
	{
		collision = run_block(gd, dir, (t_wall *)(tmp->content));
		if (collision.x < 0)
		{
			tmp = tmp->next;
			continue;
		}
		buf_dist = distance_between_two_points(gd->player->position, collision);
		if (buf_dist < *dist)
		{
			*dist = buf_dist;
			record_col = collision;
		}
		tmp = tmp->next;
	}
	return (record_col);
	// if (record_col.x >= 0.0f)
	//	 my_pixel_put(g_mlx->img, record_col.y * map_multi, record_col.x * map_multi, 0x00FF00);
}

void	draw_col(t_game_data *gd, t_fpoint collision,
	float dist, int col)
{
	const float dist_to_full_screen = 0.5f;

	int height = gd->res.y * (dist_to_full_screen / dist);
	if (height > gd->res.y)
		height = gd->res.y;
	int px_start = 0 + (gd->res.y - height) / 2;
	int px_end = gd->res.y - (gd->res.y - height) / 2;

	for (int i = px_start; i < px_end; i++)
	{
		// my_pixel_put(g_mlx->img, gd->res.x - col - 1, i,
		// 	my_pixel_get(g_mlx->texture_east,
		// 	(int)(shift * g_mlx->texture_east->width),
		// 	(int)(((float)(i - px_start) / (px_end - px_start)) * g_mlx->texture_east->height)));
		my_pixel_put(g_mlx->img, gd->res.x - col - 1, i, 0xAAAAAA);
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
	// ft_memcpy(g_mlx->img->addr, g_mlx->bg->addr, gd->res.x
	// 	* gd->res.y * (g_mlx->img->bpp / 8));
	for (int i = 0; i < gd->res.x; i++)
	{
		dist = INT_MAX;
		collision = cast_ray(gd, i, &dist);
		if (collision.x < 0.0f)
			continue ;
		my_pixel_put(g_mlx->img, collision.y * map_multi, collision.x * map_multi, 0xAAAAAA);
		draw_col(gd, collision, dist, i);
	}
	draw_map(gd);
}
