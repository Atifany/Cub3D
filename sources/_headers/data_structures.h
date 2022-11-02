/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:33:29 by atifany           #+#    #+#             */
/*   Updated: 2022/11/02 17:13:17 by atifany          ###   ########.fr       */
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
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

// Stores graphics info
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*bg;
	t_img	*texture_north;
	t_img	*texture_west;
	t_img	*texture_east;
	t_img	*texture_south;
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

// Stores gameplay info
typedef struct s_game_data
{
	float		player_speed;
	float		player_rot_speed;
	char		**map;
	t_transform	*player;
	int			fov;
	t_point		res;
	t_list		*keys_pressed;
	int			floor;
	int			ceiling;
	bool		is_focused;
}	t_game_data;

#endif
