
EXIT= exit/clean_map.c

INIT= init/init_content.c init/init_map.c init/loaders.c init/get_map_ent.c

PARSING= parsing/found_utils.c parsing/validate_textures.c \
		parsing/validate_map.c parsing/utils.c parsing/validate_rgb.c

UTILS=

DEBUG= utils/debugging_utils.c

RENDER= render/render.c

VECTORS= vectors/vector_helpers.c


FILES = main.c $(PARSING) $(INIT) $(VECTORS) $(UTILS) $(EXIT) $(DEBUG) #$(RENDER)