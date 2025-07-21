C = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -Iincludes

# Directories
SRCDIR = src
ODIR = ofiles
LIBFTDIR = libft
# Source and object files
RENDER =
PARSER =
SRC = main.c $(addprefix $(SRCDIR)/,$(RENDER) $(PARSER))
OBJS = $(addprefix $(ODIR)/,$(notdir $(SRC:.cpp=.o)))
# Dependencies
DEPS = $(OBJS:.o=.d)

# Executable name
NAME = cub3D

all: $(NAME) $(LIBFTDIR)

$(NAME): $(OBJS)
	$(C) $(CFLAGS) $(OBJS) -o $(NAME)

$(ODIR)/%.o: $(SRCDIR)/%.cpp | $(ODIR)
	$(C) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
