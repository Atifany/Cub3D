
#ifndef CUB3D_H
# define CUB3D_H
// Standart libs
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
// Embedded libs
# include "../../libs/libft/libft.h"
# include "../../libs/mlx/mlx.h"
// Embedded headers
# include "data_structures.h"

// General macros
# define READ 0		// never touch 'em
# define WRITE 1	// never touch 'em
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
// Keycodes
# define ESC_KEY 53

int do_smt(t_mlx_data	*mlx_data);
// Hooks
int	key_hook(int keycode, t_mlx_data *m_d);
int	die_hook(t_mlx_data *m_d);
// Utils
void	error_die(t_mlx_data *m_d, char *error_text, int exit_status);

#endif
