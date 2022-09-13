
#include "../_headers/cub3d.h"

// // Tmp func -> delete later
// static void	show_linked_list(void *content)
// {
// 	printf("%d\n", *(int *)content);
// }

int	mouse_move(int x, int y, t_game_data *g_d)
{
	(void)y;
	if (x != g_d->resolution.x / 2)
	{
		rotate_player((float)(- x + g_d->resolution.x / 2) * g_d->player_rot_speed, g_d);
		mlx_mouse_move(g_mlx->mlx, g_mlx->win, g_d->resolution.x / 2, g_d->resolution.y / 2);
	}
	return (0);
}

// printf("Pressed key: %d\n", keycode);
// ft_lstiter(g_d->keys_pressed, show_linked_list);
int	key_down_hook(int keycode, t_list **keys_pressed)
{
	t_list	*tmp;
	int		*buf;

	//printf("Key down active\n");
	tmp = *keys_pressed;
	while (tmp && tmp->next && *(int *)(tmp->next->content) != keycode)
		tmp = tmp->next;
	if (!tmp || (!(tmp->next) && *(int *)(tmp->content) != keycode))
	{
		buf = (int *)ft_calloc(1, sizeof(int));
		*buf = keycode;
		ft_lstadd_back(keys_pressed, ft_lstnew(buf));
	}
	return (0);
}

// printf("Releazed key: %d\n", keycode);
// ft_lstiter(g_d->keys_pressed, show_linked_list);
int	key_up_hook(int keycode, t_list **keys_pressed)
{
	t_list	*tmp;
	t_list	*buf;

	//printf("Key release active\n");
	if (!*keys_pressed)
		return (0);
	if (*(int *)((*keys_pressed)->content) == keycode)
	{
		buf = (*keys_pressed)->next;
		ft_lstdelone(*keys_pressed, free);
		*keys_pressed = buf;
		if (!(*keys_pressed))
			*keys_pressed = NULL;
	}
	tmp = *keys_pressed;
	while (tmp && tmp->next)
	{
		if (*(int *)(tmp->next->content) == keycode)
		{
			buf = tmp->next->next;
			ft_lstdelone(tmp->next, free);
			tmp->next = buf;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

static bool	is_in_list(t_list *lst, int target)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if ((*(int *)(tmp->content)) == target)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void	list_active_keys(t_game_data *g_d)
{
	int	mousex;
	int	mousey;
	if (is_in_list(g_d->keys_pressed, ESC))
		error_die(g_d, "Cub3D: Esc key was presssed.\n", 0);
	if (is_in_list(g_d->keys_pressed, W) && !is_in_list(g_d->keys_pressed, A) && !is_in_list(g_d->keys_pressed, D))
		move_player((t_fpoint){g_d->player_speed, 0.0f}, g_d);
	if (is_in_list(g_d->keys_pressed, A) && !is_in_list(g_d->keys_pressed, W) && !is_in_list(g_d->keys_pressed, S))
		move_player((t_fpoint){0.0f, -1 * g_d->player_speed}, g_d);
	if (is_in_list(g_d->keys_pressed, S) && !is_in_list(g_d->keys_pressed, A) && !is_in_list(g_d->keys_pressed, D))
		move_player((t_fpoint){-1 * g_d->player_speed, 0.0f}, g_d);
	if (is_in_list(g_d->keys_pressed, D) && !is_in_list(g_d->keys_pressed, S) && !is_in_list(g_d->keys_pressed, W))
		move_player((t_fpoint){0.0f, g_d->player_speed}, g_d);
	
	if (is_in_list(g_d->keys_pressed, W) && is_in_list(g_d->keys_pressed, A))
		move_player((t_fpoint){g_d->player_speed / 2, g_d->player_speed / -2}, g_d);
	if (is_in_list(g_d->keys_pressed, W) && is_in_list(g_d->keys_pressed, D))
		move_player((t_fpoint){g_d->player_speed / 2, g_d->player_speed / 2}, g_d);
	if (is_in_list(g_d->keys_pressed, S) && is_in_list(g_d->keys_pressed, A))
		move_player((t_fpoint){g_d->player_speed / -2, g_d->player_speed / -2}, g_d);
	if (is_in_list(g_d->keys_pressed, S) && is_in_list(g_d->keys_pressed, D))
		move_player((t_fpoint){g_d->player_speed / -2, g_d->player_speed / 2}, g_d);
	
	mlx_mouse_get_pos(g_mlx->mlx, g_mlx->win, &mousex, &mousey);
	mouse_move(mousex, mousey, g_d);
	if (is_in_list(g_d->keys_pressed, L_ARROW))
		rotate_player(g_d->player_rot_speed, g_d);
	if (is_in_list(g_d->keys_pressed, R_ARROW))
		rotate_player(-1 * g_d->player_rot_speed, g_d);
}

void	update(t_game_data *g_d)
{
	list_active_keys(g_d);
	draw_frame(g_d);
	mlx_put_image_to_window(g_mlx->mlx, g_mlx->win, g_mlx->img->img, 0, 0);
	mlx_destroy_image(g_mlx->mlx, g_mlx->img->img);
}

unsigned long s = 0;
//18494660 / 3023759
int loop_hook(t_game_data *g_d)
{
	static int clock1 = 0;
	if (s == 0)
		s = clock();
	if (clock1++ < 0/*TICKS_PER_UPDATE*/)
		return 0;
	else
	{
		clock1 = 0;
		if (g_d->player->view_angle++ >= 360)
		{
			printf("%ld\n", clock() - s);
			g_d->player->view_angle = 0;
			s = 0;
		}
		update(g_d);
	}
	return (0);
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, "Cub3D: Exit button was pressed.\n", 0);
	return (0);
}
