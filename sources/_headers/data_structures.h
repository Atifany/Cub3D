/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:33:29 by atifany           #+#    #+#             */
/*   Updated: 2022/11/16 17:29:51 by atifany          ###   ########.fr       */
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
	int		bypp;
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
	float		view_angle_h;
	float		view_angle_v;
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
	t_transform	*player;
	int			fov;
	t_point		res;
	t_list		*keys_pressed;
	bool		is_focused;
	float		focal_length;
}	t_game_data;

#endif
