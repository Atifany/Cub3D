
#ifndef CUB3D_H
# define CUB3D_H

// Standart libs
# include <stdio.h>
# include <stdbool.h>
// Embedded libs
# include "../../libs/libft/libft.h"
# include "../../libs/mlx/mlx.h"
// Embedded headers
# include "data_structures.h"
# include "get_next_line.h"

// General macros
# define READ 0		// never touch 'em
# define WRITE 1	// never touch 'em
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
// Keycodes
# define ESC_KEY 53

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
// Map processing
bool	is_valid_input(int argc);
bool	parse_file(t_game_data *g_d, char *file_path);
bool	is_valid_file(char *file_path);
// TMP <- delete them later
void	display_charpp(char **arr);

#endif
