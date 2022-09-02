
#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

// Exterior libraries
# include <stdbool.h>

// Stores graphics info
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
}	t_mlx_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// typedef struct s_wall
// {
// 	t_point	*v1;
// 	t_point	*v2;
// }	t_wall;

typedef struct s_player_transform
{
	t_point	position;
	float		view_angle;
}	t_transform;

// Stores gameplay info
typedef struct s_game_data
{
	char		**map;
	t_transform	*player;
	int			fov;
}	t_game_data;

#endif
