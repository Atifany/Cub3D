#include "../_headers/cub3d.h"

void	*ft_realloc(void *ptr, size_t size, size_t oldsize)
{
	// add a proper free function as a parametre.
	int				i;
	unsigned char	*ret;
	unsigned char	*ptr_cpy;

	ptr_cpy = ptr;
	if (size == 0)
		return (NULL);
	ret = malloc(size);
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

void	error_die(t_game_data *g_d, char *error_text, int exit_status)
{
	if (g_d && g_mlx)
	{
		mlx_destroy_window(g_mlx->mlx, g_mlx->win);
		free(g_mlx);
		destroy_g_d(g_d);
	}
	printf("%s", error_text);
	exit(exit_status);
}
