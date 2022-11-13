/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:39:23 by atifany           #+#    #+#             */
/*   Updated: 2022/11/13 15:59:12 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// do not remove this comment
// do not forget to get back flags in makefile!!!
// recheck leaks in parser,
//	 because there is no leak-checker capable of doing so on linux!

#ifndef CUB3D_H
# define CUB3D_H

// Standart libs
# include <X11/X.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
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
# include "error_codes.h"

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

# endif // GLOBAL

// Inits
int				init_window(t_game_data *g_d);
void			init_g_d_defaults(t_game_data *g_d);
t_img			*init_textures(char *path, char* name);
t_img			*create_background(t_game_data *g_d);

// Hooks
void			list_active_keys(t_game_data *g_d);
void			simple_press_hook(int keycode, t_game_data *g_d);
int				key_down_hook(int keycode, t_game_data *g_d);
int				key_up_hook(int keycode, t_list **keys_pressed);
int				mouse_move(int x, int y, t_game_data *g_d);
int				die_hook(t_game_data *g_d);
void			update(t_game_data *g_d);
int				loop_hook(t_game_data *g_d);
void			set_new_mouse_pos(int x, int y);
void			get_mouse_pos(int *mousex, int *mousey);

// Utils
int				ft_strcmp(char *str1, char *str2);
void			error_die(t_game_data *g_d, int err_code, int exit_status);
void			free_array(char **arr);
double			dabs(double x);
double			deg_to_rad(float a);
void			set_player_transform(t_game_data *g_d,
					t_fpoint position, int view_angle);
float			fto_pos(float x);
void			*ft_realloc_charpp(void *ptr, size_t size, size_t oldsize);
void			destroy_g_d(t_game_data *g_d);

// Map processing
// new:
int				parse_textures(char** file_text);
int				parse_map(t_game_data* g_d, char** file_text);
int				charpp_length(char** arr);
//
int				parse_file(t_game_data *g_d, char *file_path);
bool			is_valid_file(char *file_path);
bool			is_valid_map(char **file_text);
int				parse_head(char **file_text, t_game_data *g_d);
char			**read_file(char *file_path);
char			**cut_trailings(char **file_text);
void			clean_spaces(t_game_data *g_d, char **cut_text);
int				find_right_border(char *line);
int				find_left_border(char *line);
bool			is_spawner(char c);
char			*multiply_line(char *line);
char			**multiply_size(char **cut_text);
int				count_items_charpp(char **charpp);

// Map process utils
bool			is_valid_color(char *r, char *g, char *b);
void			parse_player(t_game_data *g_d, int x, int y, char dir);
int				read_texture(void *texture, char *split_line);
int				read_color(void *color_hex, char *color_line);
void			write_line_to_map(char *cut_text, char **map);

// Parsing head functions
t_head_map		*init_head_map(t_game_data *g_d);
int				parse_head_line(t_head_map **h_map, char **split_line);

// Movement
int				move_player(t_fpoint shift, t_game_data *g_d);
int				rotate_player(float shift, t_game_data *g_d);

// Focus change hooks
void			focus_change_button(t_game_data *g_d);
int				focus_in(t_game_data *g_d);
int				focus_out(t_game_data *g_d);

// TMP <- delete them later
void			display_charpp(char **arr);

// Graphics
void			my_pixel_put(t_img *img, int x, int y, unsigned int color);
unsigned int	darker(int c, int d);
void			draw_map(t_game_data *gd);
void			draw_frame(t_game_data *gd);
int				loop_hook(t_game_data *g_d);
unsigned int	my_pixel_get(t_img *img, int x, int y);
double			deg_to_rad(float a);

#endif
