#include "../_headers/cub3d.h"
#include "../_headers/data_structures.h"

void	my_pixel_put(int x, int y, int color)
{
	char	*dst;
	dst = g_mlx->img->addr + (y * g_mlx->img->line_length + x * (g_mlx->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

int draw_line(int col, t_point collision, t_game_data *gd)
{
    int i;
    float d = distance(collision, (gd->player->position)) * 64 / MAP_RES;

    if ((d < 256))
    {
        float h = 0;
        h = (float)(gd->resolution.y*10)/(float)d;
        i = (gd->resolution.y - h) / 2;
		int c = 0;
        while (c < h && i < gd->resolution.y)
        {
			if (i >= 0)
				my_pixel_put(col, i, darker(my_pixel_get(g_mlx->texture, (collision.x+collision.y)/2 % 64, (int)(2*c/(h/64))%64), d));
			i++;
			c++;
        }
    }
	return (0);
}
		 
t_point cast_ray(t_game_data *gd, int col)
{
	t_point ret = {-1, -1};
	float dir_x = unsigned int(cos(deg_to_rad(gd->player->view_angle - 45 + ((float)gd->fov) / ((float)gd->resolution.x) * ((float)col)))); //zamenit' float na int perem
	float dir_y = unsigned int(sin(deg_to_rad(gd->player->view_angle - 45 + ((float)gd->fov) / ((float)gd->resolution.x) * ((float)col)))); // ispolzovat int kak peremennuu s statichnoy tochkoy
	float fx = gd->player->position.x;
	float fy = gd->player->position.y;
	int i = -1;
	while (++i < MAP_RES >> 2)
	{
		fx += dir_x*((2 << (i >> 10)+1));// map_res / 64
		fy += dir_y*((2 << (i >> 10)+1));
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

	my_pixel_put(gd->player->position.x/(MAP_RES/8), gd->player->position.y/(MAP_RES/8), 0x00800000);
	while (gd->map[i])
	{
		j = 0;
		while (gd->map[i][j])
		{
			if (gd->map[i][j] == '1')
				my_pixel_put(i/(MAP_RES/8), j/(MAP_RES/8), 0x00ff0000);
			j+=MAP_RES/8;
		}
		i+=MAP_RES/8;
	}
}

int draw_frame(t_game_data *gd)
{
    int	i;
    t_point collision;

    g_mlx->img->img = mlx_new_image(g_mlx->mlx, 1920, 1080);
    g_mlx->img->addr = mlx_get_data_addr(g_mlx->img->img, &g_mlx->img->bits_per_pixel, &g_mlx->img->line_length,
								&g_mlx->img->endian);
	i = -1;
	while (++i < gd->resolution.x) // можно уменьшить разрешение
	{
		collision = cast_ray(gd, gd->resolution.x - i);
		if (collision.x >= 0)
			draw_line(i, collision, gd);
	}
	draw_map(gd);
	return (0);
}
