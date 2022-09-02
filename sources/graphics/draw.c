#include "../_headers/cub3d.h"
#include "../_headers/data_structures.h"

int draw_pixel(t_mlx_data	*mlx_data, int x, int y)
{
    mlx_pixel_put(mlx_data->mlx, mlx_data->win, x, y, 0x00FFFFFF);
}

int draw_line(t_mlx_data	*mlx_data, int x1, int y1, int x2, int y2)
{
    int p = abs(x1 - x2) + abs(y1 - y2);

    int i = -1;
    while (++i < p+1)
    {
        int x = x1 + i * (x2 - x1) / p;
        int y = y1 + i * (y2 - y1) / p;

        draw_pixel(mlx_data, x, y);
    }
}

int draw_square(t_mlx_data	*mlx_data, int x, int y)
{
    draw_line(mlx_data, x,y,x + 100, y);
    draw_line(mlx_data, x,y,x, y + 100);
    draw_line(mlx_data, x + 100, y + 100, x + 100, y);
    draw_line(mlx_data, x + 100, y + 100, x , y + 100);
}

int do_smt(t_mlx_data	*mlx_data)
{
    draw_square(mlx_data, 100, 100);
    //draw_line(mlx_data, 100,100,100 + 1000, 100 + 1);git 
    draw_square(mlx_data, 500, 900);
    return 0;
}