
#include "../_headers/cub3d.h"

void	focus_change_button(t_game_data *g_d)
{
	if (g_d->is_focused == true)
		focus_out(g_d);
	else
		focus_in(g_d);
}

void	set_new_mouse_pos(int x, int y)
{
	#ifdef __APPLE__
	mlx_mouse_move(g_mlx->win, x, y);
	#endif
	#ifdef __linux__
	mlx_mouse_move(g_mlx->mlx, g_mlx->win, x, y);
	#endif
}

void	get_mouse_pos(int *mousex, int *mousey)
{
	#ifdef __APPLE__
	mlx_mouse_get_pos(g_mlx->win, mousex, mousey);
	#endif
	#ifdef __linux__
	mlx_mouse_get_pos(g_mlx->mlx, g_mlx->win, mousex, mousey);
	#endif
	
}

int	focus_in(t_game_data *g_d)
{
	#ifdef __APPLE__
	mlx_mouse_hide();
	#endif
	#ifdef __linux__
	mlx_mouse_hide(g_mlx->mlx, g_mlx->win);
	#endif
	
	g_d->is_focused = true;
	set_new_mouse_pos(g_d->res.x / 2, g_d->res.y / 2);
	return (0);
}

int	focus_out(t_game_data *g_d)
{
	#ifdef __APPLE__
	mlx_mouse_show();
	#endif
	#ifdef __linux__
	mlx_mouse_show(g_mlx->mlx, g_mlx->win);
	#endif
	g_d->is_focused = false;
	return (0);
}

// // Tmp func -> delete later
// static void	show_linked_list(void *content)
// {
// 	printf("%d\n", *(int *)content);
// }

int	mouse_move(int x, int y, t_game_data *g_d)
{
	(void)y;
	if (!g_d->is_focused)
		return (0);
	if (x != g_d->res.x / 2)
	{
		rotate_player((float)(- x + g_d->res.x / 2) * g_d->player_rot_speed, g_d);
		set_new_mouse_pos(g_d->res.x / 2, g_d->res.y / 2);
	}
	return (0);
}

// printf("Pressed key: %d\n", keycode);
// ft_lstiter(g_d->keys_pressed, show_linked_list);
int	key_down_hook(int keycode, t_game_data *g_d)
{
	t_list	*tmp;
	int		*buf;

	if (keycode == Q)
		focus_change_button(g_d);
	tmp = g_d->keys_pressed;
	while (tmp && tmp->next && *(int *)(tmp->next->content) != keycode)
		tmp = tmp->next;
	if (!tmp || (!(tmp->next) && *(int *)(tmp->content) != keycode))
	{
		buf = (int *)ft_calloc(1, sizeof(int));
		*buf = keycode;
		ft_lstadd_back(&(g_d->keys_pressed), ft_lstnew(buf));
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
		error_die(g_d, 8, 0);
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

	get_mouse_pos(&mousex, &mousey);
	mouse_move(mousex, mousey, g_d);
	if (is_in_list(g_d->keys_pressed, L_ARROW))
		rotate_player(g_d->player_rot_speed * 10, g_d);
	if (is_in_list(g_d->keys_pressed, R_ARROW))
		rotate_player(-1 * g_d->player_rot_speed * 10, g_d);
}

static long long cur_time(long long timestart)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	if (!timestart)
		return (milliseconds);
	return (milliseconds - timestart);
}

static void display_fps(t_game_data *g_d)
{	
	static int			oldfps = 0;
	static int			fps = 0;
	static long long	secs = 0;
	static long long	timestart = 0;
	char				*string_to_display;

	if (!timestart)
		timestart = cur_time(0);
	fps++;
	if (cur_time(timestart) / 1000 > secs / 1000)
	{
		oldfps = fps;
		fps = 0;
	}
	string_to_display = ft_itoa(oldfps);
	mlx_string_put(g_mlx->mlx, g_mlx->win,
			g_d->res.x - 100, 50,
			0x00FFFFFF, string_to_display);
	free(string_to_display);
	secs = cur_time(timestart);
}

void	update(t_game_data *g_d)
{
	static long long lastframe = 0;
	if (cur_time(lastframe) > 30)
	{
		lastframe = cur_time(0);
		list_active_keys(g_d);
		draw_frame(g_d);
		mlx_put_image_to_window(g_mlx->mlx, g_mlx->win, g_mlx->img->img, 0, 0);
		display_fps(g_d);
		mlx_destroy_image(g_mlx->mlx, g_mlx->img->img);
	}
}

int loop_hook(t_game_data *g_d)
{
	update(g_d);
	return (0);
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, 9, 0);
	return (0);
}
