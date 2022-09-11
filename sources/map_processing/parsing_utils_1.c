#include "../_headers/cub3d.h"

void	parse_player_transform(t_game_data *g_d, int x, int y, char dir)
{
	t_fpoint	position;
	int			view_angle;

	view_angle = 180;
	position.x = (x + 1) * MAP_RES - MAP_RES / 2;
	position.y = (y + 1) * MAP_RES - MAP_RES / 2;
	if (dir == 'W')
		view_angle = 270;
	else if (dir == 'E')
		view_angle = 90;
	else if (dir == 'S')
		view_angle = 0;
	set_player_transform(g_d, position, view_angle);
}
