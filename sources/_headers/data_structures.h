/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:33:29 by atifany           #+#    #+#             */
/*   Updated: 2022/11/11 20:57:33 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

// Exterior libraries
# include <stdbool.h>

// parser helper for function mapping
typedef struct s_head_map
{
	char	*id;
	int		(*read_f)(void *, char *);
	void	*obj;
	bool	is_found;
}	t_head_map;

typedef struct s_img
{
	char	*name;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

// Stores graphics info
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	t_img	*img;
	// t_img	*bg;
	// t_img	*texture_north;
	// t_img	*texture_west;
	// t_img	*texture_east;
	// t_img	*texture_south;
	t_list	*textures;
}	t_mlx_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
}	t_fpoint;

typedef struct s_player_transform
{
	t_fpoint	size;
	t_fpoint	position;
	float		view_angle;
}	t_transform;

typedef struct s_wall
{
	t_fpoint	v1;
	t_fpoint	v2;
	t_img*		texture;
}	t_wall;

// Stores gameplay info
typedef struct s_game_data
{
	float		player_speed;
	float		player_rot_speed;
	t_list		*scene;
	// char		**map;
	t_transform	*player;
	int			fov;
	t_point		res;
	t_list		*keys_pressed;
	// int			floor;
	// int			ceiling;
	bool		is_focused;
}	t_game_data;

#endif
