#include "../_headers/cub3d.h"

static int	*count_collisions(t_game_data *g_d, t_fpoint new_pos)
{
	int	i;
	int	j;
	int	iend;
	int	jend;
	int	istart;
	int	jstart;
	int	*ret;

	ret = (int *)ft_calloc(8, sizeof(int));
	iend = new_pos.x + (g_d->player->size.x / 2);
	istart = new_pos.x - (g_d->player->size.x / 2);
	jend = new_pos.y + (g_d->player->size.y / 2);
	jstart = new_pos.y - (g_d->player->size.y / 2);
	i = istart;
	while (i < iend)
	{
		j = jstart;
		while (j < jend)
		{
			if (g_d->map[i][j] == '1')
			{
				if (i <= new_pos.x && j - jstart <= i - istart)
					ret[0]++;
				else if (j <= new_pos.y && j - jstart >= i - istart)
					ret[1]++;
				else if (j >= new_pos.y && j + i - istart <= jend - 1)
					ret[2]++;
				else if (i <= new_pos.x && j + i - istart >= jend - 1)
					ret[3]++;
				else if (i >= new_pos.x && j + i - istart <= jend - 1)
					ret[4]++;
				else if (j <= new_pos.y && j + i - istart >= jend - 1)
					ret[5]++;
				else if (j >= new_pos.y && j - jstart <= i - istart)
					ret[6]++;
				else if (i >= new_pos.x && j - jstart >= i - istart)
					ret[7]++;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

static int	*is_collision(t_game_data *g_d, t_fpoint new_pos)
{
	int *collisions;
	int	*count;

	count = count_collisions(g_d, new_pos);
	//printf("[%d:%d:%d:%d:%d:%d:%d:%d]\n",
	//	count[0], count[1], count[2], count[3],
	//	count[4], count[5], count[6], count[7]);
	collisions = (int *)ft_calloc(4, sizeof(int));
	collisions[NORTH] = ((count[1] >= count[0] && count[1]) || (count[2] >= count[3] && count[2]));
	collisions[EAST] = ((count[3] >= count[2] && count[3]) || (count[7] >= count[6] && count[7]));
	collisions[SOUTH] = ((count[5] >= count[4] && count[5]) || (count[6] >= count[7] && count[6]));
	collisions[WEST] = ((count[0] >= count[1] && count[0]) || (count[4] >= count[5] && count[4]));
	free(count);
	return (collisions);
}

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
	//printf("{%d:%d:%d:%d}\n", ret[NORTH], ret[SOUTH], ret[EAST], ret[WEST]);
	if ((!ret[NORTH] && new_pos.x < g_d->player->position.x)
		|| (!ret[SOUTH] && new_pos.x >= g_d->player->position.x))
		g_d->player->position.x = new_pos.x;
	if ((!ret[WEST] && new_pos.y < g_d->player->position.y)
		|| (!ret[EAST] && new_pos.y >= g_d->player->position.y))
		g_d->player->position.y = new_pos.y;
	free(ret);
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
