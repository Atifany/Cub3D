/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:26:43 by hnickole          #+#    #+#             */
/*   Updated: 2022/11/14 17:27:30 by atifany          ###   ########.fr       */
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

void	my_pixel_put_range(t_img *img, int x, int y1, int y2, unsigned int color)
{
	const char	*col = img->addr + x * img->bypp;
	const int	y_start = y1 * img->line_length;
	const int	y_end = y2 * img->line_length;

	for (int y = y_start; y <= y_end; y+=img->line_length)
	{
		*((unsigned int*)(y + col)) = color;
	}
}

unsigned int	my_pixel_get(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->addr
		+ y * img->line_length + x * img->bypp));
}
