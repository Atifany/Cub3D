
#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

// Exterior libraries
# include <stdbool.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// Stores graphics info
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*texture;
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
	t_point		resolution;
	t_list		*keys_pressed; // active keys
}	t_game_data;

#endif
