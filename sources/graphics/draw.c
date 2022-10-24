#include "../_headers/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	*((unsigned int*)(img->addr + (y * img->line_length + x * (img->bits_per_pixel >> 3)))) = color;
}

unsigned int	my_pixel_get(t_img *img, int x, int y)
{
	return *(unsigned int*)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
}

double	deg_to_rad(float a)
{
	return (a * M_PI / 180); // уменьшить точность Пи для увеличения производительности
}

float distance(t_point p1, t_fpoint p2)
{
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2))); // написать свою функцию нахождения квадратов от 1 до дальности прорисовки^2 (это дохуя)
}

unsigned int darker(int c, int d)
{
	unsigned char r = c >> 16;
	unsigned char g = c >> 8;
	unsigned char b = c;
	
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
	return (r << 16 ) + (g << 8) + b;
}



int draw_line(int col, t_point collision, t_game_data *gd, t_img *texture)
{
    int i; // index пикселя по вертикали
    float d = distance(collision, (gd->player->position)) * 64 / MAP_RES;

    if ((d < 256))
    {
		int c = 0;   // номер пикселя стены который сейчас отрисовывается
        int h = 0; // кол пикселей kotoroe стена zanimaet на экранe;
        h = (gd->resolution.y*16)/(d);
        if (d >= 16)
			i = (gd->resolution.y - h) >> 1;
		else
		{
			i = 0;
			c = (h - gd->resolution.y) >> 1;
		}
		int t_x = (collision.x+collision.y)/2 % 128;
        while (c < h && i < gd->resolution.y)
        {
			int j = h >> 8;
			unsigned int t_pixel = darker(my_pixel_get(texture, t_x, ((c << 7)/h)%128), d);
			while (j-- >= 0 && i < gd->resolution.y)
			{
				my_pixel_put(g_mlx->img, col, i, t_pixel);
				i++;
				c++;
			}
        }
    }
	return (0);
}

t_point cast_ray(t_game_data *gd, int col)
{
	t_point ret = {-1, -1};
	float dir_x = (cos(deg_to_rad(gd->player->view_angle - 45 + ((float)gd->fov) / ((float)gd->resolution.x) * ((float)col)))); //zamenit' float na int perem
	float dir_y = (sin(deg_to_rad(gd->player->view_angle - 45 + ((float)gd->fov) / ((float)gd->resolution.x) * ((float)col)))); // ispolzovat int kak peremennuu s statichnoy tochkoy
	float fx = gd->player->position.x;
	float fy = gd->player->position.y;
	int i = -1;
	while (++i < MAP_RES)
	{
		fx += dir_x*((1 << (i >> 8)));
		fy += dir_y*((1 << (i >> 8)));
		if (gd->map[(int)fx][(int)fy] == '1')
		{
			while (gd->map[(int)fx][(int)fy] == '1')
			{
				fx -= dir_x;
				fy -= dir_y;
			}
			ret.x = (int)(fx + dir_x);
			ret.y = (int)(fy + dir_y);
			return (ret);
		}
	}
	return (ret);
}

void draw_map(t_game_data *gd)
{
	int i = 0;
	int j = 0;

	my_pixel_put(g_mlx->img, gd->player->position.x/(MAP_RES/8), gd->player->position.y/(MAP_RES/8), 0x00800000);
	while (gd->map[i])
	{
		j = 0;
		while (gd->map[i][j])
		{
			if (gd->map[i][j] == '1')
				my_pixel_put(g_mlx->img, i/(MAP_RES/8), j/(MAP_RES/8), 0x00ff0000);
			j+=MAP_RES/8;
		}
		i+=MAP_RES/8;
	}
}

int draw_frame(t_game_data *gd)
{
    int	i;
    t_point collision;
	t_img	*texture;
    g_mlx->img->img = mlx_new_image(g_mlx->mlx, gd->resolution.x, gd->resolution.y);
    g_mlx->img->addr = mlx_get_data_addr(g_mlx->img->img, &g_mlx->img->bits_per_pixel, &g_mlx->img->line_length,
								&g_mlx->img->endian);
	ft_memcpy(g_mlx->img->addr, g_mlx->bg->addr, gd->resolution.x*gd->resolution.y*(g_mlx->img->bits_per_pixel / 8));

	i = -1;
	while (++i < gd->resolution.x) // можно уменьшить разрешение
	{
		collision = cast_ray(gd, gd->resolution.x - i);
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
