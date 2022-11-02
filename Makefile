# executable
NAME := cub3D

# sources
_SRC :=	core/main.c								\
		core/body.c								\
		core/inits.c							\
		graphics/draw.c							\
		graphics/pixel_operations.c				\
		graphics/calculations.c					\
		hooks/hooks.c							\
		hooks/focus_hooks.c						\
		hooks/mouse_hooks.c						\
		hooks/key_hooks.c						\
		hooks/process_user_input.c				\
		utils/utils.c							\
		utils/utils_1.c							\
		map_processing/validation.c				\
		map_processing/parsing_core.c			\
		map_processing/parsing_functions.c		\
		map_processing/parse_head_functions.c	\
		map_processing/parsing_utils.c			\
		map_processing/parsing_utils_1.c		\
		movement/movement.c						\

# sources preparation
SRC_DIR := sources
SRC := $(_SRC:%=$(SRC_DIR)/%)
# tester source list
_SRCT := $(filter-out core/main.c, $(_SRC))
SRCT := $(_SRCT:%=$(SRC_DIR)/%)
SRCT += "tests/tests.c"
# tmp files
OBJ := $(SRC:%.c=%.o)
DPS := $(SRC:%.c=%.d)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_FLAGS += -lXext -lX11
    LIBS := -lm
    MLX_DIR := libs/mlx_linux_1/
else
    MLX_FLAGS += -framework OpenGL -framework AppKit
    MLX_DIR := libs/mlx/
endif

# libraries
LIBFT_DIR := libs/libft/
LIBFT := libft.a

MLX := libmlx.a
LIBS +=	$(LIBFT:%=$(LIBFT_DIR)%) \
		$(MLX:%=$(MLX_DIR)%)

# flags
#C_FLAGS += -O2 -Wall -Wextra -Werror

# Make commands
CC := gcc
RM := rm -f

# rules
all: compile_libs start

start: log_compile_start $(NAME)

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

test: compile_libs
	@$(MAKE) start NAME="test.out" SRC="$(SRCT)"

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