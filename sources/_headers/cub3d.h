
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
# define MAP_RES 1024
# define TICKS_PER_UPDATE 10000
# define MAP_ALLOWED_LIST "01NWSE \t\n\r\v\f"
# define PLAYER_SIZE MAP_RES / 8
// mlx event codes
# define ON_KEYDOWN 2
# define ON_KEYUP 3
// # define ON_MOUSEMOVE
// # define ON_MOUSEPRESS
# define ON_DESTROY 17
// Direction
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

// Global
# ifndef GLOBAL
#  define GLOBAL

extern t_mlx_data	*g_mlx;

# endif

// Hooks
int	key_down_hook(int keycode, t_list **keys_pressed);
int	key_up_hook(int keycode, t_list **keys_pressed);
int	die_hook(t_game_data *g_d);
int	move_player(int keycode, t_game_data *g_d);
int	rotate_player(int keycode, t_game_data *g_d);
void	update(t_game_data *g_d);
int loop_hook(t_game_data *g_d);
// Utils
void	error_die(t_game_data *g_d, char *error_text, int exit_status);
void	init_g_d_defaults(t_game_data *g_d);
void	free_array(char **arr);
double	dabs(double x);
double	deg_to_rad(float a);
void	set_player_transform(t_game_data *g_d, t_fpoint position, int view_angle);
float	fto_pos(float x);
// Map processing
bool	parse_file(t_game_data *g_d, char *file_path);
bool	is_valid_input(int argc);
bool	is_valid_file(char *file_path);
bool	is_valid_map(char **file_text);
char	**read_file(char *file_path);
char	**cut_trailings(char **file_text);
void	clean_spaces(t_game_data *g_d, char **cut_text);
int		find_right_border(char *line);
int		find_left_border(char *line);
bool	is_spawner(char c);
char	*multiply_line(char *line);
char	**multiply_size(char **cut_text);
int		count_items_charpp(char **charpp);
void	parse_player_transform(t_game_data *g_d, int x, int y, char dir);

// Movement
int	move_player(int keycode, t_game_data *g_d);
int	rotate_player(int keycode, t_game_data *g_d);

// TMP <- delete them later
void	display_charpp(char **arr);

void draw_map(t_game_data *gd);
int draw_frame(t_game_data *gd);
int loop_hook(t_game_data *g_d);

#include <time.h>

#endif
