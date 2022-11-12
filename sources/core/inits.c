/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:38:28 by atifany           #+#    #+#             */
/*   Updated: 2022/11/12 12:56:20 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

// t_img	*create_background(t_game_data *g_d)
// {
// 	t_img	*image;
// 	int		x;
// 	int		y;
//
// 	image = malloc(sizeof(t_img));
// 	image->img = mlx_new_image(g_mlx->mlx, g_d->res.x, g_d->res.y);
// 	image->addr = mlx_get_data_addr(image->img, &image->bpp,
// 			&image->line_length, &image->endian);
// 	y = 0;
// 	while (y < g_d->res.y)
// 	{
// 		x = 0;
// 		while (x < g_d->res.x)
// 		{
// 			if (y < g_d->res.y >> 1)
// 				my_pixel_put(image, x, y, darker(g_d->ceiling, (sqrt(y)) * 11));
// 			else
// 				my_pixel_put(image, x, y,
// 					darker(g_d->floor, (sqrt(g_d->res.y - y)) * 11));
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (image);
// }

static void	null_textures( void )
{
	g_mlx->textures = NULL;
}

int	init_window(t_game_data *g_d)
{
	g_mlx = (t_mlx_data *)ft_calloc(1, sizeof(t_mlx_data));
	g_mlx->mlx = mlx_init();
	if (!g_mlx->mlx)
		return (1);
	g_mlx->img = ft_calloc(1, sizeof(t_img));
	g_mlx->img->line_length = g_d->res.x;
	g_mlx->win = mlx_new_window(g_mlx->mlx,
			g_d->res.x, g_d->res.y, "Cub3D");
	if (!g_mlx->win)
		return (1);
	null_textures();
	return (0);
}

t_img	*init_textures(char *path, char* name)
{
	t_img	*image;

	image = malloc(sizeof(t_img));
	image->img = mlx_xpm_file_to_image(g_mlx->mlx, path,
		&(image->width), &(image->height));
	if (!image->img)
	{
		free(image);
		return (NULL);
	}
	image->name = ft_strdup(name);
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (image);
}
