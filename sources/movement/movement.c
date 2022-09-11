#include "../_headers/cub3d.h"

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
// add a case if e.g. 'W' and 'D' are pressed together.
int	move_player(t_fpoint shift, t_game_data *g_d)
{
	float		cos_dir;
	float		sin_dir;
	t_fpoint	new_pos;
	int			*ret;

	cos_dir = cos(deg_to_rad(g_d->player->view_angle));
	sin_dir = sin(deg_to_rad(g_d->player->view_angle));
	new_pos.x = g_d->player->position.x + shift.x * cos_dir + shift.y * sin_dir;
	new_pos.y = g_d->player->position.y + shift.x * sin_dir - shift.y * cos_dir;

	ret = is_collision(g_d, new_pos);
	//printf("[%d:%d:%d:%d]\n", ret[NORTH], ret[SOUTH], ret[EAST], ret[WEST]);
	if ((!ret[NORTH] && cos_dir < 0) || (!ret[SOUTH] && cos_dir >= 0))
		g_d->player->position.x = new_pos.x;
	if ((!ret[WEST] && sin_dir < 0) || (!ret[EAST] && sin_dir >= 0))
		g_d->player->position.y = new_pos.y;
	return (0);
}

int	rotate_player(float shift, t_game_data *g_d)
{
	g_d->player->view_angle += shift;
	if (g_d->player->view_angle <= 0)
		g_d->player->view_angle = 360 + g_d->player->view_angle;
	else if (g_d->player->view_angle > 360)
		g_d->player->view_angle = g_d->player->view_angle - 360;
	return (0);
}
