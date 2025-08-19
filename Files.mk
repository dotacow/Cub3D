
EXIT= exit/clean_map.c

INIT= init/init_content.c init/init_map.c init/loaders.c

PARSING= parsing/found_utils.c parsing/validate_textures.c \
		parsing/validate_map.c parsing/utils.c parsing/validate_rgb.c

UTILS= utils/memhelpers.c

RENDER= render/render.c

VECTORS= vectors/vector_helpers.c


FILES = main.c $(PARSING) $(INIT) $(VECTORS) $(UTILS) $(EXIT) #$(RENDER)