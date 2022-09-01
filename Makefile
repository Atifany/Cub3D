# executable
NAME = cub3D

# sources
_SRC =	core/main.c

SRC_DIR = sources
SRC = $(_SRC:%=$(SRC_DIR)/%)
# tmp files
OBJ = $(SRC:%.c=%.o)
DPS = $(SRC:%.c=%.d)

# libraries
LIBFT_DIR = libs/libft/
LIBFT = libft.a
MLX_DIR = libs/mlx/
MLX = libmlx.a
LIBS =	$(LIBFT:%=$(LIBFT_DIR)%) \
		$(MLX:%=$(MLX_DIR)%)

# Make commands
CC = gcc
C_FLAGS = -O2 -Wall -Wextra -Werror
MLX_FLAGS = -framework OpenGL -framework AppKit
RM = rm -f

# rules
all: compile_libs log_compile_start $(NAME)

compile_libs:
	@printf "\n>> compile libft\n"
	@make -C $(LIBFT_DIR) bonus
	@printf "\n>> compile mlx\n"
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(MLX_FLAGS) -o $@

%.o: %.c Makefile
	$(CC) $(C_FLAGS) -MMD -MP -c $< -o $@

-include $(DPS)

clean:
	@printf "\n>> clean tmp files\n"
	$(RM) $(OBJ) $(DPS)

fclean: clean
	@printf "\n>> clean executable\n"
	$(RM) $(NAME)

clean_libs:
	@printf "\n>> cleaning libft\n"
	@make -C $(LIBFT_DIR) fclean
	@printf "\n>> cleaning mlx\n"
	@make -C $(MLX_DIR) clean

re: fclean all

log_compile_start:
	@printf "\n>> compile sources\n"

.PHONY: all re clean compile_libs create_dirs clean_libs log_compile_start