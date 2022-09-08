#include "../_headers/cub3D.h"

// static t_point	is_collsion(t_game_data *g_d, t_fpoint new_pos)
// {
// 	int i;
// 	int j;
// 	int imax;
// 	int jmax;
//
// 	imax = (int)(new_pos.x + (g_d->player->size.x) / 2);
// 	jmax = (int)(new_pos.y + (g_d->player->size.y) / 2);
// 	i = (int)fto_pos((new_pos.x - (g_d->player->size.x) / 2));
// 	while (g_d->map[i] && i < imax)
// 	{
// 		j = (int)fto_pos(new_pos.y - (g_d->player->size.y) / 2);
// 		while (g_d->map[i][j] && j < jmax)
// 		{
// 			if (g_d->map[i][j] == '1')
// 				return ((t_point){i, j});
// 			j++;
// 		}
// 		i++;
// 	}
// 	return ((t_point){-1, -1});
// }

static int	check_north(t_game_data *g_d, t_fpoint new_pos)
{
	int	i;
	int	j;
	int istart;
	int jstart;
	int jend;

	int count_side = 0;
	int count_north = 0;

	// check left for wich is more
	//printf("\nTile: [%f:%f]\n", new_pos.x, new_pos.y);
	jstart = (int)(fto_pos(new_pos.y - (g_d->player->size.y / 2)));
	istart = (int)(fto_pos(new_pos.x - (g_d->player->size.x / 2)));
	i = istart;
	while (i <= (int)(new_pos.x))
	{
		j = jstart;
		while (j <= (int)(new_pos.y))
		{
			//printf("%d:%d ", i, j);
			if (g_d->map[i][j] == '1')
			{
				if (j - jstart >= i - istart)
					count_north++;
				else
					count_side++;
			}
			j++;
		}
		//printf("\n");
		i++;
	}
	//printf("[%d:%d]\n", count_north, count_side);
	if (count_north > count_side)
		return (1);
	count_side = 0;
	count_north = 0;
	jend = (int)(fto_pos(new_pos.y + (g_d->player->size.y / 2)));
	i = istart;
	while (i < (int)(new_pos.x))
	{
		j = (int)(new_pos.y);
		while (j < jend)
		{
			if (g_d->map[i][j] == '1')
			{
				if (j + i - istart < jend)
					count_north++;
				else
					count_side++;
			}
			j++;
		}
		i++;
	}
	//printf("<%d:%d>\n", count_north, count_side);
	if (count_north > count_side)
		return (1);
	return (0);
}

static int	check_east(t_game_data *g_d, t_fpoint new_pos)
{
	(void)g_d;
	(void)new_pos;
	return (0);
}

static int	check_south(t_game_data *g_d, t_fpoint new_pos)
{
	int	i;
	int	j;
	int iend;
	int jstart;
	int jend;

	int count_side = 0;
	int count_north = 0;

	// check left for wich is more
	//printf("\nTile: [%f:%f]\n", new_pos.x, new_pos.y);
	jend = (int)(fto_pos(new_pos.y + (g_d->player->size.y / 2)));
	jstart = (int)(fto_pos(new_pos.y - (g_d->player->size.y / 2)));
	iend = (int)(fto_pos(new_pos.x + (g_d->player->size.x / 2)));
	i = (int)(new_pos.x);
	while (i < iend)
	{
		j = jstart;
		while (j <= (int)(new_pos.y))
		{
			//printf("%d:%d ", i, j);
			if (g_d->map[i][j] == '1')
			{
				if (j + i - (int)(new_pos.x) >= (int)(new_pos.y))
					count_north++;
				else
					count_side++;
			}
			j++;
		}
		//printf("\n");
		i++;
	}
	//printf("[%d:%d]\n", count_north, count_side);
	if (count_north > count_side)
		return (1);
	count_side = 0;
	count_north = 0;
	i = (int)(new_pos.x);
	while (i < iend)
	{
		j = (int)(new_pos.y);
		while (j <= jend)
		{
			if (g_d->map[i][j] == '1')
			{
				if (j - (int)(new_pos.y) < i - (int)(new_pos.x))
					count_north++;
				else
					count_side++;
			}
			j++;
		}
		i++;
	}
	//printf("<%d:%d>\n", count_north, count_side);
	if (count_north > count_side)
		return (1);
	return (0);
}

static int	check_west(t_game_data *g_d, t_fpoint new_pos)
{
	(void)g_d;
	(void)new_pos;
	return (0);
}

static int	*is_collision(t_game_data *g_d, t_fpoint new_pos)
{
	int *collisions;

	collisions = (int *)ft_calloc(4, sizeof(int));
	collisions[NORTH] = check_north(g_d, new_pos);
	collisions[EAST] = check_east(g_d, new_pos);
	collisions[SOUTH] = check_south(g_d, new_pos);
	collisions[WEST] = check_west(g_d, new_pos);
	return (collisions);
}

// ADD COLLISIONS!!
// add a case if 'W' and 'D' are pressed together.
int	move_player(int keycode, t_game_data *g_d)
{
	float	sin_dir;
	float	cos_dir;
	int		*ret;

	cos_dir = g_d->player_speed * cos(deg_to_rad(g_d->player->view_angle + 45));
	sin_dir = g_d->player_speed * sin(deg_to_rad(g_d->player->view_angle + 45));
	if (keycode == W)
	{
		ret = is_collision(g_d, (t_fpoint){
			g_d->player->position.x + cos_dir,
			g_d->player->position.y + sin_dir});
		//printf("[%d:%d:%d:%d]\n", ret[NORTH], ret[SOUTH], ret[EAST], ret[WEST]);
		if ((!ret[NORTH]
			&& g_d->player->position.x >= g_d->player->position.x + cos_dir)
			|| (!ret[SOUTH]
			&& g_d->player->position.x < g_d->player->position.x + cos_dir))
		{
			g_d->player->position.x += cos_dir;
			// g_d->player->position.y += sin_dir;
		}
		if ((!ret[WEST]
			&& g_d->player->position.y >= g_d->player->position.y + sin_dir)
			|| (!ret[EAST]
			&& g_d->player->position.y < g_d->player->position.y + sin_dir))
		{
			//g_d->player->position.x += cos_dir;
			g_d->player->position.y += sin_dir;
		}
	}
	else if (keycode == A)
	{
		// ret = is_collision(g_d, (t_fpoint){
		// 	g_d->player->position.x + sin_dir,
		// 	g_d->player->position.y - cos_dir});
		// if (ret.x < 0)
		// {
			g_d->player->position.x += sin_dir;
			g_d->player->position.y -= cos_dir;
		// }
	}
	else if (keycode == S)
	{
		// ret = is_collision(g_d, (t_fpoint){
		// 	g_d->player->position.x - cos_dir,
		// 	g_d->player->position.y - sin_dir});
		// if (ret.x < 0)
		// {
			g_d->player->position.x -= cos_dir;
			g_d->player->position.y -= sin_dir;
		// }
	}
	else if (keycode == D)
	{
		// ret = is_collision(g_d, (t_fpoint){
		// 	g_d->player->position.x - sin_dir,
		// 	g_d->player->position.y + cos_dir});
		// if (ret.x < 0)
		// {
			g_d->player->position.x -= sin_dir;
			g_d->player->position.y += cos_dir;
		// }
	}
	else
		return (1);
	return (0);
}

int	rotate_player(int keycode, t_game_data *g_d)
{
	if (keycode == L_ARROW)
	{
		if (g_d->player->view_angle <= 0)
			g_d->player->view_angle = 360;
		else
			g_d->player->view_angle -= g_d->player_rot_speed;
	}
	else if (keycode == R_ARROW)
	{
		if (g_d->player->view_angle >= 360)
			g_d->player->view_angle = 0;
		else
			g_d->player->view_angle += g_d->player_rot_speed;
	}
	else
		return (1);
	return (0);
}
