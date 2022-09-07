
#include "../_headers/cub3d.h"

// // Tmp func -> delete later
// static void	show_linked_list(void *content)
// {
// 	printf("%d\n", *(int *)content);
// }

// printf("Pressed key: %d\n", keycode);
// ft_lstiter(g_d->keys_pressed, show_linked_list);
int	key_down_hook(int keycode, t_list **keys_pressed)
{
	t_list	*tmp;
	int		*buf;

	tmp = *keys_pressed;
	while (tmp && tmp->next && *(int *)(tmp->next->content) != keycode)
		tmp = tmp->next;
	if (!tmp || (!(tmp->next) && *(int *)(tmp->content) != keycode))
	{
		buf = (int *)ft_calloc(1, sizeof(int));
		*buf = keycode;
		ft_lstadd_back(keys_pressed, ft_lstnew(buf));
		//printf("Pressed key: %d\n", keycode);
		//ft_lstiter(*keys_pressed, show_linked_list);
	}
	return (0);
}

// printf("Releazed key: %d\n", keycode);
// ft_lstiter(g_d->keys_pressed, show_linked_list);
int	key_up_hook(int keycode, t_list **keys_pressed)
{
	t_list	*tmp;
	t_list	*buf;

	
	if (!*keys_pressed)
		return (0);
	if (*(int *)((*keys_pressed)->content) == keycode)
	{
		buf = (*keys_pressed)->next;
		ft_lstdelone(*keys_pressed, free);
		*keys_pressed = buf;
		if (!(*keys_pressed))
			*keys_pressed = NULL;
		//printf("Releazed key: %d\n", keycode);
		//ft_lstiter(*keys_pressed, show_linked_list);
	}
	tmp = *keys_pressed;
	while (tmp && tmp->next)
	{
		if (*(int *)(tmp->next->content) == keycode)
		{
			buf = tmp->next->next;
			ft_lstdelone(tmp->next, free);
			tmp->next = buf;
			//printf("Releazed key: %d\n", keycode);
			//ft_lstiter(*keys_pressed, show_linked_list);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	do_activated_key(int keycode, t_game_data *g_d)
{
	if (keycode == ESC)
		error_die(g_d, "Cub3D: Esc key was presssed.\n", 0);
	if (move_player(keycode, g_d) && rotate_player(keycode, g_d))
		printf("Uncaught key was pressed: %d\n", keycode);
}

void	update(t_game_data *g_d)
{
	t_list	*tmp;

	tmp = g_d->keys_pressed;
	while (tmp)
	{
		do_activated_key(*(int *)tmp->content, g_d);
		tmp = tmp->next;
	}
	// autorotate
	// g_d->player->view_angle += 1;
	// if (g_d->player->view_angle == 361)
	// 	g_d->player->view_angle = 0;
	draw_frame(g_d);
	mlx_put_image_to_window(g_mlx->mlx, g_mlx->win, g_mlx->img, 0, 0);
	mlx_destroy_image(g_mlx->mlx, g_mlx->img);
}

//unsigned long s = 0;
//18494660 / 3023759
int loop_hook(t_game_data *g_d)
{
	static int clock1 = 0;
	//if (s == 0)
	//	s = clock();
	if (clock1++ < 0/*TICKS_PER_UPDATE*/)
		return 0;
	else
	{
		clock1 = 0;
		//if (g_d->player->view_angle++ >= 360)
		//{
		//	printf("%ld\n", clock() - s);
		//	g_d->player->view_angle = 0;
		//	s = 0;
		//}

		update(g_d);
	}
	return (0);
}

int	die_hook(t_game_data *g_d)
{
	error_die(g_d, "Cub3D: Exit button was pressed.\n", 0);
	return (0);
}

// key listenings:
// int[<All listened keys>][2] :
// [ 'A'
//  Hold
//
