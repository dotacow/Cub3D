C = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -MMD -MP -Iincludes -I$(MLXDIR)/include -I$(LIBFTDIR)/includes -Ofast #only use one of g3 or Ofast at a time for best results
LDFLAGS = -L$(LIBFTDIR) -L$(MLXDIR)/build -lft -lmlx42 -lm -ldl -lglfw
# Directories
SRCDIR = src
ODIR = ofiles
LIBFTDIR = libft
MLXDIR = MLX42
# Source files:
RENDER =
PARSER =
FILES = main.c
SRC = $(addprefix $(SRCDIR)/, $(FILES))
OBJS = $(addprefix $(ODIR)/,$(FILES:.c=.o))
# Dependencies
DEPS = $(OBJS:.o=.d)
# libraries
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx42.a
# Executable name
NAME = cub3D

all: $(NAME) $(LIBFT) $(MLX)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(ODIR)/%.o: $(SRCDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLX):
	cmake -S$(MLXDIR) -B$(MLXDIR)/build
	make -C $(MLXDIR)/build -j4


clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(MLXDIR)/build
	rm -rf $(ODIR)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
