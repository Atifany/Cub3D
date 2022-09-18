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

bool	is_valid_color(char *r, char *g, char *b)
{
	int	i;

	if ((!r && !*r) || (!g && !*g) || (!b && !*b))
		return (false);
	if (ft_strlen(r) > 3 || ft_strlen(g) > 3 || ft_strlen(b) > 3)
		return (false);
	i = 0;
	while (r[i])
		if (!ft_isdigit(r[i++]))
			return (false);
	i = 0;
	while (g[i])
		if (!ft_isdigit(g[i++]))
			return (false);
	i = 0;
	while (b[i])
		if (!ft_isdigit(b[i++]))
			return (false);
	if (ft_atoi(r) > 255 || ft_atoi(r) < 0
		|| ft_atoi(g) > 255 || ft_atoi(g) < 0
		|| ft_atoi(b) > 255 || ft_atoi(b) < 0)
		return (false);
	return (true);
}
