/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:26:43 by hnickole          #+#    #+#             */
/*   Updated: 2022/11/13 15:58:31 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

// add a function to add a line at once
// with memcpy(img + addr, color, number_of_pixels)

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	*((unsigned int*)(img->addr + (y * img->line_length
			+ x * img->bypp))) = color;
}

unsigned int	my_pixel_get(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->addr
		+ y * img->line_length + x * img->bypp));
}
