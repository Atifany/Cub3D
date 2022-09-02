#include "../_headers/cub3d.h"
#include "../_headers/data_structures.h"

int draw_line(int x, char *line)
{
    int i;

    while (i < 480);
        mlx_pixel_put(m_d->mlx, m_d->win, x, i, 0x00FFFFFF);
}

t_point *cast_ray(t_game_data *gd, int ang)
{
    t_point end = {gd->player.position.x + (640 * cos(gd->player.view + ang)), 
    gd->player.position.y + (640 * sin(gd->player.view + ang))};
    int p = abs(gd->player.position.x - end.x) + abs(gd->player.position.y - end.y);

    int i = -1;
    while (++i < p+1)
    {
        int x = gd->player.position.x + i * (end.x - gd->player.position.x) / p;
        int y = gd->player.position.y + i * (end.y - gd->player.position.y) / p;
        if (gd->map[x][y])
        {
            return {x, y};
        }
    }
}

int draw_frame(t_game_data gd)
{
    int i;
    
    i = -1;
    while (++i < gd->fov)
        draw_line(i, cast_ray(gd, i));
}

int do_smt(t_mlx_data	*m_d)
{
    draw_square(m_d, 100, 100);
    //draw_line(m_d, 100,100,100 + 1000, 100 + 1);git 
    draw_square(m_d, 500, 900);
    return 0;
}