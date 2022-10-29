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

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	*((unsigned int*)(img->addr + (y * img->line_length
			+ x * (img->bpp >> 3)))) = color;
}

unsigned int	my_pixel_get(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->addr
		+ (y * img->line_length + x * (img->bpp / 8))));
}

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

int	draw_line(int col, t_point collision, t_game_data *gd, t_img *texture)
{
	int		i;
	float	d;
	int		c;
	int		h;

	c = 0;
	d = distance(collision, (gd->player->position)) * 64 / MAP_RES;
	if ((d < 256))
	{
		h = (gd->res.y * 16) / d;
		if (d >= 16)
			i = (gd->res.y - h) >> 1;
		else
		{
			i = 0;
			c = (h - gd->res.y) >> 1;
		}
		int t_x = (collision.x+collision.y) / 2 % 128;
		while (c < h && i < gd->res.y)
		{
			int				j = h >> 8;
			unsigned int	t_pixel = darker(my_pixel_get(texture, t_x, ((c << 7) / h) % 128), d);
			while (j-- >= 0 && i < gd->res.y)
			{
				my_pixel_put(g_mlx->img, col, i, t_pixel);
				i++;
				c++;
			}
		}
	}
	return (0);
}

void	init_points(t_fpoint *dir, t_fpoint *pos, t_game_data *gd, int col)
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

void	draw_map(t_game_data *gd)
{
	int	i;
	int	j;

	i = 0;
	my_pixel_put(g_mlx->img, gd->player->position.y / (MAP_RES / 8), gd->player->position.x / (MAP_RES / 8), 0x00800000);
	while (gd->map[i])
	{
		j = 0;
		while (gd->map[i][j])
		{
			if (gd->map[i][j] == '1')
				my_pixel_put(g_mlx->img, j / (MAP_RES / 8),
					i / (MAP_RES / 8), 0x00ff0000);
			j += MAP_RES / 8;
		}
		i += MAP_RES / 8;
	}
}

int	draw_frame(t_game_data *gd)
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
	return (0);
}
