#include "../_headers/cub3d.h"

void	*ft_realloc_charpp(void *ptr, size_t size, size_t oldsize)
{
	int				i;
	unsigned char	*ret;
	unsigned char	*ptr_cpy;

	ptr_cpy = ptr;
	if (size == 0)
		return (NULL);
	ret = malloc(size);
	//printf("{%-20s%p}\n", "ft_realloc:", ret);
	if (!ret)
		return (ptr);
	if (!ptr || oldsize == 0)
		return (ret);
	i = 0;
	while (i < oldsize && i < size)
	{
		ret[i] = ptr_cpy[i];
		i++;
	}
	free(ptr);
	return (ret);
}

void	destroy_g_d(t_game_data *g_d)
{
	if (!g_d)
		return ;
	if (g_d->map)
		free_array(g_d->map);
	if (g_d->player)
		free(g_d->player);
	ft_lstclear(&(g_d->keys_pressed), free);
	free(g_d);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1)
		str1 = STR_EMPTY;
	if (!str2)
		str2 = STR_EMPTY;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

void	error_die(t_game_data *g_d, int err_code, int exit_status)
{
	char *error_texts[] = {
		/*0*/ "Cub3D: Error: Initialization failed.\n",
		/*1*/ "Cub3D: Error: Invalid input.\nUsage: ./cub3D [filename].cub\n",
		/*2*/ "Cub3D: Error: Invalid filename.\n",
		/*3*/ "Cub3D: Error: Cannot open given file.\n",
		/*4*/ "Cub3D: Error: Invalid map.\n",
		/*5*/ "Cub3D: Error: Wrong floor color.\n",
		/*6*/ "Cub3D: Error: Wrong ceiling color.\n",
		/*7*/ "Cub3D: Error: File's head is corrupted.\n",
		/*8*/ "Cub3D: Esc key was presssed.\n",
		/*9*/ "Cub3D: Exit button was pressed.\n"
		/*10*/ "Cub3D: Error: Texture not found\n"
	};
	if (g_d)
		destroy_g_d(g_d);
	if (g_mlx)
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
	printf("%s", error_texts[err_code]);
	exit(exit_status);
}

void display_charpp(char** arr)
{
	int i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		printf("%s\n", arr[i++]);
		//sleep(500000);
	}
}
