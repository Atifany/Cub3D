#include "../_headers/cub3d.h"
#include "../_headers/data_structures.h"

////define PI 3.14159265359

void	my_pixel_put(int x, int y, int color)
{
	char	*dst;

	dst = g_mlx->addr + (y * g_mlx->line_length + x * (g_mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	deg_to_rad(float a)
{
	return (a * M_PI / 180); // уменьшить точность Пи для увеличения производительности
}

int distance(t_point p1, t_fpoint p2)
{
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2))); // написать свою функцию нахождения квадратов от 1 до дальности прорисовки^2 (это дохуя)
}

int draw_line(int col, t_point collision, t_game_data *gd)
{
    //printf("drawing_line\n");
    int i;
    int d = distance(collision, (gd->player->position)) * 64 / MAP_RES;
    int color = 0x00ffffff;

    if ((d < 256))
    {
        int h = 0;
        color -= (0x00010101*(d));
        h = gd->resolution.y*10/d;
        if (h > gd->resolution.y)
            h = gd->resolution.y; 
        i = (gd->resolution.y - h) / 2;
        // printf("%d %d\n", h, d);
        while (h-- && i < gd->resolution.y)
        {
            my_pixel_put(col, i, color);
            i++;
        }
    }
	return (0);
}
		 
t_point cast_ray(t_game_data *gd, int col)
{
    t_point ret;

   // printf("casting_ray to x: %d y: %d\n", end.x, end.y);
   // printf(" at angle %.6f\n", gd->player->view_angle + (float)gd->fov / (float)640 * (float)col);
	
    //
	float dir_x = cos(deg_to_rad(gd->player->view_angle + ((float)gd->fov) / ((float)gd->resolution.x) * ((float)col)));// триг. функции работают очень долго(можно составить массив заранее вычисленных значений)
	float dir_y = sin(deg_to_rad(gd->player->view_angle + ((float)gd->fov) / ((float)gd->resolution.x) * ((float)col)));// 360*разрешение экрана/на угол обзора
																									 // sin_tab[gd->player->view_angle * gd.x_res / gd.fov + col]
	float fx = gd->player->position.x;
	float fy = gd->player->position.y;
	//	
    int i = -1;
    while (++i < MAP_RES*8)
    {
		fx += dir_x;
		fy += dir_y;
        if (gd->map[(int)fx][(int)fy] == '1')
        {
            ret.x = (int)fx;
            ret.y = (int)fy;
        	//if (ret.x<= 0 || ret.y <= 0 || ret.x > 5*64|| ret.y > 6*64)
		//		return ret;
		//printf("ray_collision at %d %d\n", ret.x, ret.y);
		//mlx_pixel_put(g_mlx->mlx, g_mlx->win, ret.x+10, ret.y+10, 0x00ffffff);
		return ret;
       }
    }
	return (ret);
}

void draw_map(t_game_data *gd)
{
	int i = 0;
	int j = 0;
	while (gd->map[i])
		while (gd->map[i][j])
			my_pixel_put(i, j, 0xff0000);
}

int draw_frame(t_game_data *gd)
{
    int	i;
    t_point collision;

    g_mlx->img = mlx_new_image(g_mlx->mlx, 1920, 1080);
    g_mlx->addr = mlx_get_data_addr(g_mlx->img, &g_mlx->bits_per_pixel, &g_mlx->line_length,
								&g_mlx->endian);
	draw_map(gd);
    i = -1;
	while (++i < gd->resolution.x) // можно уменьшить разрешение
	{
		collision = cast_ray(gd, i);
		draw_line(i, collision, gd);
		if (collision.x - gd->player->position.x > 0 && collision.y - gd->player->position.y + 100)
			my_pixel_put(collision.x - gd->player->position.x + 100, collision.y - gd->player->position.y + 100, 0xff0000);
	}
	return (0);
}
