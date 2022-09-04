#include "../_headers/cub3d.h"
#include "../_headers/data_structures.h"

////define PI 3.14159265359

double	deg_to_rad(float a)
{
	return (a * M_PI / 180); // уменьшить точность Пи для увеличения производительности
}

int distance(t_point p1, t_point p2)
{
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2))); // написать свою функцию нахождения квадратов от 1 до дальности прорисовки^2 (это дохуя)
}

int draw_line(int col, t_point collision, t_game_data *gd)
{
    //printf("drawing_line\n");
    int i;
    int d = distance(collision, (gd->player->position));
    int color = 0x00ffffff;

    if ((d < 256))
    {
        color -= (0x00010101*(d));
        int h = 0;
        if (d > 40)
            h = 19200/d;
        
        
        i = 480-h /2;
       // printf("%d %d\n", h, d);
        while (h--)
        {
            mlx_pixel_put(g_mlx->mlx, g_mlx->win, col, i, color);
            i++;
        }
    }
}

float create_sin_table(float *arr, t_game_data *gd)
{
	float c = gd.x_res/gd.fov;
	arr = malloc(360*c*sizeof(float));
	int i = 0;
	
	while(i < 360*c)
	{
		arr[i] = sin(deg_to_rad((float)i/c);
		i++;
	}
}

float create_cos_table(float *arr, t_game_data *gd)
{
	float c = gd.x_res/gd.fov;
	arr = malloc(360*c*sizeof(float));
	int i = 0;
	
	while(i < 360*c)
	{
		arr[i] = cos(deg_to_rad((float)i/c);
		i++;
	}
}
		 

t_point cast_ray(t_game_data *gd, int col)
{
    t_point ret;

   // printf("casting_ray to x: %d y: %d\n", end.x, end.y);
   // printf(" at angle %.6f\n", gd->player->view_angle + (float)gd->fov / (float)640 * (float)col);
	
    //
	float dir_x = cos(deg_to_rad(gd->player->view_angle + (float)gd->fov / (float)640 * (float)col));// триг. функции работают очень долго(можно составить массив заранее вычисленных значений)
	float dir_y = sin(deg_to_rad(gd->player->view_angle + (float)gd->fov / (float)640 * (float)col));// 360*разрешение экрана/на угол обзора
																									 // sin_tab[gd->player->view_angle * gd.x_res / gd.fov + col]
	float fx = gd->player->position.x;
	float fy = gd->player->position.y;
	//	
    int i = -1;
    while (++i < 512)
    {
		fx += dir_x;
		fy += dir_y;
        if (gd->map[(int)fx][(int)fy])
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
}

int draw_frame(t_game_data *gd)
{
    //printf("drawing_frame\n");
    //for (int i = 0; i < 5*64; i++)
    //{
    //    for (int j = 0; j < 5*64; j++)
    //    {
    //            printf("%d", gd->map[i][j]);
    //    }
    //    printf("\n");
    //}
    int i;
    i = -1;
    while (++i < 640) // можно ууменьшить разрешение
        draw_line(i, cast_ray(gd, i), gd);
}
