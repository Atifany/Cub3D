/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:16:07 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 22:27:59 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

void	simple_press_hook(int keycode, t_game_data *g_d)
{
	if (keycode == Q)
		focus_change_button(g_d);
}

// printf("Pressed key: %d\n", keycode);
// ft_lstiter(g_d->keys_pressed, show_linked_list);
int	key_down_hook(int keycode, t_game_data *g_d)
{
	t_list	*tmp;
	int		*buf;

	simple_press_hook(keycode, g_d);
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

	if (!*keys_pressed)
		return (0);
	if (*(int *)((*keys_pressed)->content) == keycode)
	{
		buf = (*keys_pressed)->next;
		ft_lstdelone(*keys_pressed, free);
		*keys_pressed = buf;
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
