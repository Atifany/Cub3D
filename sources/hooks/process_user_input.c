/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:36:40 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 23:14:09 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

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

static void	rotate(t_game_data *g_d)
{
	int		mousex;
	int		mousey;

	get_mouse_pos(&mousex, &mousey);
	mouse_move(mousex, mousey, g_d);
	if (is_in_list(g_d->keys_pressed, L_ARROW))
		rotate_player(g_d->player_rot_speed * 10, g_d);
	if (is_in_list(g_d->keys_pressed, R_ARROW))
		rotate_player(-1 * g_d->player_rot_speed * 10, g_d);
}

void	list_active_keys(t_game_data *g_d)
{
	float	xa;
	float	ya;

	xa = 0.0f;
	ya = 0.0f;
	if (is_in_list(g_d->keys_pressed, ESC))
		error_die(g_d, KEYPRESS_ESC_KEY, 0);
	if (is_in_list(g_d->keys_pressed, W))
		xa += g_d->player_speed / 2;
	if (is_in_list(g_d->keys_pressed, A))
		ya -= g_d->player_speed / 2;
	if (is_in_list(g_d->keys_pressed, S))
		xa -= g_d->player_speed / 2;
	if (is_in_list(g_d->keys_pressed, D))
		ya += g_d->player_speed / 2;
	if (dabs(dabs(xa) - dabs(ya)) > g_d->player_speed / 4)
	{
		xa *= 2;
		ya *= 2;
	}
	move_player((t_fpoint){xa, ya}, g_d);
	rotate(g_d);
}
