/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:26:43 by hnickole          #+#    #+#             */
/*   Updated: 2022/10/29 19:28:26 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	*((unsigned int*)(img->addr + (y * img->line_length
			+ x * (img->bpp >> 3)))) = color;
}

unsigned int	my_pixel_get(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->addr
		+ (y * img->line_length + x * (img->bpp / 8))));
}
