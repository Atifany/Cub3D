
#ifndef CUB3D_H
# define CUB3D_H

// Standart libs
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
// Embedded libs
# include "../../libs/libft/libft.h"

# ifdef __APPLE__
#  include "../../libs/mlx/mlx.h"
#  include "keycodes_macos.h"

# elif __linux__
#  include "../../libs/mlx_linux_1/mlx.h"
#  include "keycodes_linux.h"
# endif

// Embedded headers
# include "data_structures.h"
# include "get_next_line.h"

// General macros
# define READ 0		// never touch 'em
# define WRITE 1	// never touch 'em
# define MAP_SIZE_MULTI 64
# define TICKS_PER_UPDATE 10000

// Global
# ifndef GLOBAL
#  define GLOBAL

extern t_mlx_data	*g_mlx;

# endif

// Hooks
int	key_hook(int keycode, t_game_data *g_d);
int	die_hook(t_game_data *g_d);
// Utils
void	error_die(t_game_data *g_d, char *error_text, int exit_status);
void	init_g_d_defaults(t_game_data *g_d);
void	free_array(char **arr);
double	dabs(double x);
double	deg_to_rad(float a);
void	set_player_transform(t_game_data *g_d, t_point position, int view_angle);
// Map processing
bool	is_valid_input(int argc);
bool	parse_file(t_game_data *g_d, char *file_path);
bool	is_valid_file(char *file_path);
// TMP <- delete them later
void	display_charpp(char **arr);

int draw_frame(t_game_data *gd);
int loop_hook(t_game_data *g_d);

#endif
