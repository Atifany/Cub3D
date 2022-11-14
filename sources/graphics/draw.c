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

typedef struct s_collision
{
	t_wall		*wall;
	t_fpoint	collision;
	float		texture_shift;
}	t_collision;

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
		my_pixel_put(g_mlx->img, cur.y, cur.x, 0xFF0000);
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

void is_intersect_segments(t_fpoint p1, t_fpoint p2, t_fpoint p3, t_fpoint p4,
	t_collision *collision)
{
	const float d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / d;
	const float u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x)) / d;
	(*collision).texture_shift = u;
	if (!(0 < u && u < 1 && t > 0))
	{
		(*collision).collision = (t_fpoint){-1.0f, -1.0f};
		return ;
	}
	(*collision).collision = (t_fpoint){p3.x + u * (p4.x - p3.x), p3.y + u * (p4.y - p3.y)};
}

// this func is actually a rudimentary one, but can be usefull
// for calculating collisions for a more complex figures then a line segment.
t_collision run_block(t_game_data *gd, t_fpoint dir, t_wall* wall)
{
	t_collision collision;
	float buf_dist = -1.0f;
	float record_dist = INT_MAX;
	t_collision record_col = {wall, (t_fpoint){-1.0f, -1.0f}, -1.0f};

	is_intersect_segments(
		gd->player->position,
		(t_fpoint){dir.x, dir.y}, wall->v1, wall->v2, &collision);
	if (collision.collision.x <= 0.0f)
		return (record_col);
	buf_dist = distance_between_two_points(
		gd->player->position, collision.collision);
	if (buf_dist < record_dist)
	{
		record_dist = buf_dist;
		record_col.collision = collision.collision;
		record_col.texture_shift = collision.texture_shift;
	}
	return (record_col);
}

static t_collision cast_ray(t_game_data *gd, int col, float* dist)
{
	const float angle = gd->player->view_angle - (float)(gd->fov / 2)
				+ (((float)(gd->fov) / (float)(gd->res.x)) * (float)(col));
	const t_fpoint dir = {
		gd->player->position.x + cos(deg_to_rad(angle)),
		gd->player->position.y + sin(deg_to_rad(angle))};
	
	t_collision collision;
	float buf_dist = -1.0f;
	t_collision record_col = {NULL, (t_fpoint){-1.0f, -1.0f}, -1.0f};

	// runs through all the objects on the map
	t_list* tmp = gd->scene;
	while (tmp != NULL)
	{
		collision = run_block(gd, dir, (t_wall *)(tmp->content));
		if (collision.collision.x < 0)
		{
			tmp = tmp->next;
			continue;
		}
		buf_dist = distance_between_two_points(
			gd->player->position, collision.collision);
		if (buf_dist < *dist)
		{
			*dist = buf_dist;
			record_col.collision = collision.collision;
			record_col.texture_shift = collision.texture_shift;
			record_col.wall = collision.wall;
		}
		tmp = tmp->next;
	}
	return (record_col);
}

void	draw_col(t_game_data *gd, t_collision collision,
	float dist, int col)
{
	// add a shift from the top, wich will be contolled by the mouse
	// the mouse looks up - shift increases, and vica versa.
	// todo: make it work with that shift. then controll it with mouse.
	const float dist_to_full_screen = 1.0f;

	float tx_start = 0;
	float tx_end = collision.wall->texture->height;
	int px_height = gd->res.y * (dist_to_full_screen / dist);
	if (px_height > gd->res.y)
	{
		float tx_height = (float)collision.wall->texture->height
			* (dist_to_full_screen / dist);
		tx_start = ((float)collision.wall->texture->height / 2)
			* (1.0f - (float)collision.wall->texture->height / tx_height);
		tx_end = (float)collision.wall->texture->height - tx_start;
		px_height = gd->res.y;
	}
	const int px_start = 0 + (gd->res.y - px_height) / 2;
	const int px_end = gd->res.y - px_start;

	// these const variables help to get ~2.75fps
	// the formula is following:
	// percentage_of_pixels_on_screen_passed
	//	* tx_pixels_to_pass
	//	+ where_to_start_reading_texture
	// where percentage_of_pixels_on_screen_passed = (cur_pixel - pixel_start) / pixels_to_pass
	const float a = (tx_end - tx_start) / (px_end - px_start);
	const float a1 = (float)px_start * a - tx_start;
	const int x = (float)collision.texture_shift * (float)(collision.wall->texture->width);
	const int col_to_px = gd->res.x - col - 1;

	// with the help of these guys I call pixel_get only when I know I will
	// get a new pixel from the texture, because before, cycle called
	// for a new pixel from the texture every time it drew a pixel to the screen
	// which was significantly more often then it should. Now it calls for a
	// new pixel only texture->width times.
	int tx_change = -1;
	int cur_tx_line = 0;
	int last_px = px_start;

	for (int i = px_start; i < px_end; i++)
	{
		cur_tx_line = (int)((float)(i * a) - a1);
		if (cur_tx_line != tx_change)
		{
			my_pixel_put_range(g_mlx->img, col_to_px, last_px, i,
				my_pixel_get(collision.wall->texture, x, cur_tx_line));
			tx_change = cur_tx_line;
			last_px = i;
		}

		// old way.
		// my_pixel_put(g_mlx->img, col_to_px, i,
		// 	my_pixel_get(collision.wall->texture, x, (int)((float)(i * a) - a1)));
	}
	my_pixel_put_range(g_mlx->img, col_to_px, last_px, px_end,
		my_pixel_get(collision.wall->texture, x, cur_tx_line));
}

void	draw_frame(t_game_data *gd)
{
	float		dist;
	t_collision	collision;
	t_img		*texture;

	// new frame init
	g_mlx->img->img = mlx_new_image(g_mlx->mlx, gd->res.x, gd->res.y);
	g_mlx->img->addr = mlx_get_data_addr(g_mlx->img->img, &g_mlx->img->bpp,
			&g_mlx->img->line_length, &g_mlx->img->endian);
	g_mlx->img->bypp = g_mlx->img->bpp / 8;

	for (int i = 0; i < gd->res.x; i++)
	{
		dist = INT_MAX;
		collision = cast_ray(gd, i, &dist);
		if (collision.collision.x < 0.0f) // no collision detected
			continue ;
		draw_col(gd, collision, dist, i);
	}
	draw_map(gd);
}
