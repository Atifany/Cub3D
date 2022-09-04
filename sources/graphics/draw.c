#include "../_headers/cub3d.h"
#include "../_headers/data_structures.h"

double	deg_to_rad(float a)
{
	return (a * M_PI / 180); // уменьшить точность Пи для увеличения производительности
}

int distance(t_point p1, t_point p2)
{
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
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
	return (0);
}

t_point cast_ray(t_game_data *gd, int col)
{
    t_point end = {gd->player->position.x + (640 * cos(deg_to_rad(gd->player->view_angle + (float)gd->fov / (float)640 * (float)col))), // приведение к флоат занимает много времени 
    gd->player->position.y + (640 * sin(deg_to_rad(gd->player->view_angle + (float)gd->fov / (float)640 * (float)col)))}; // триг. функции работают очень долго(можно составить массив заранее вычисленных значений)
    int p = abs(gd->player->position.x - end.x) + abs(gd->player->position.y - end.y);                                    // Можно использовать другой способ вычисления точки в которую пускается луч или использовать другой алгоритм пуска луча 
    t_point ret;

   // printf("casting_ray to x: %d y: %d\n", end.x, end.y);
   // printf(" at angle %.6f\n", gd->player->view_angle + (float)gd->fov / (float)640 * (float)col);

    int i = -1;
    while (++i < p+1)
    {
        int x = gd->player->position.x + i * (end.x - gd->player->position.x) / p; // Заместо этого можно создать флотовый вектор направления
        int y = gd->player->position.y + i * (end.y - gd->player->position.y) / p; // и прибавлять его в этом цикле к координатам игрока
        if (gd->map[x][y])
        {
            ret.x = x;
            ret.y = y;
            //if (ret.x<= 0 || ret.y <= 0 || ret.x > 5*64|| ret.y > 6*64)
		//		return ret;

			//printf("ray_collision at %d %d\n", ret.x, ret.y);
		mlx_pixel_put(g_mlx->mlx, g_mlx->win, ret.x+10, ret.y+10, 0x00ffffff);
		return ret;
       }
    }
	return (ret);
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
    int	i;
	
    i = -1;
	while (++i < 640) // можно уменьшить разрешение
		draw_line(i, cast_ray(gd, i), gd);
	return (0);
}
