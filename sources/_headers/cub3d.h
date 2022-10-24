// do not remove this comment
// do not forget to get back flags in makefile!!!
//
// I guess it leaks when validator shows error

#ifndef CUB3D_H
# define CUB3D_H

// Standart libs
# include <X11/X.h>
# include <sys/time.h>
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
# define PLAYER_SIZE_MULTY 8
# define STR_EMPTY ""
// mlx event codes
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEMOVE 6
# define ON_FOCUS_IN 9
# define ON_FOCUS_OUT 10
# define ON_DESTROY 17
# define KEYMAP_NOTIFY 11
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
int		key_down_hook(int keycode, t_list **keys_pressed);
int		key_up_hook(int keycode, t_list **keys_pressed);
int		mouse_move(int x, int y, t_game_data *g_d);
int		die_hook(t_game_data *g_d);
void	update(t_game_data *g_d);
int		loop_hook(t_game_data *g_d);
int		focus_in(t_game_data *g_d);
int		focus_out(t_game_data *g_d);
// Utils
t_img	*init_textures(char *path, t_game_data *g_d);
int		ft_strcmp(char *str1, char *str2);
void	error_die(t_game_data *g_d, char *error_text, int exit_status);
void	init_g_d_defaults(t_game_data *g_d);
void	free_array(char **arr);
double	dabs(double x);
double	deg_to_rad(float a);
void	set_player_transform(t_game_data *g_d,
			t_fpoint position, int view_angle);
float	fto_pos(float x);
void	*ft_realloc(void *ptr, size_t size, size_t oldsize);
// Map processing
bool	parse_file(t_game_data *g_d, char *file_path);
bool	is_valid_input(int argc);
bool	is_valid_file(char *file_path);
bool	is_valid_map(char **file_text);
int		parse_head(char **file_text, t_game_data *g_d);
char	**read_file(char *file_path);
char	**cut_trailings(char **file_text);
void	clean_spaces(t_game_data *g_d, char **cut_text);
int		find_right_border(char *line);
int		find_left_border(char *line);
bool	is_spawner(char c);
char	*multiply_line(char *line);
char	**multiply_size(char **cut_text);
int		count_items_charpp(char **charpp);
// Map process utils
bool	is_valid_color(char *r, char *g, char *b);
void	parse_player_transform(t_game_data *g_d, int x, int y, char dir);
bool	read_textures(int *count, char **split_line, t_game_data *g_d);
bool	read_color(int *count, char **split_line, t_game_data *g_d);
void	write_line_to_map(char *cut_text, char **map);

// Movement
int		move_player(t_fpoint shift, t_game_data *g_d);
int		rotate_player(float shift, t_game_data *g_d);

// TMP <- delete them later
void	display_charpp(char **arr);

float distance(t_point p1, t_fpoint p2);
void	my_pixel_put(t_img *img, int x, int y, int color);
unsigned int darker(int c, int d);
void draw_map(t_game_data *gd);
int draw_frame(t_game_data *gd);
int loop_hook(t_game_data *g_d);

#include <sys/time.h>

//colors
# define BLK "\e[0;30m"
# define BBLK "\e[1;30m"
# define RED "\e[0;31m"
# define BRED "\e[1;31m"
# define GRN "\e[0;32m"
# define BGRN "\e[1;32m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"
# define BLU "\e[0;34m"
# define BBLU "\e[1;34m"
# define MAG "\e[0;35m"
# define BMAG "\e[1;35m"
# define CYN "\e[0;36m"
# define BCYN "\e[1;36m"
# define WHT "\e[0;37m"
# define BWHT "\e[1;37m"
# define NC "\e[0m"

#endif
