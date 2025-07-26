RENDER= render.c

INIT=

#EXIT= exit/utils.c

PARSER= parsing/found_utils.c parsing/validate_textures.c \
		parsing/validate_map.c parsing/utils.c parsing/validate_rgb.c

FILES = main.c $(PARSER) #$(INIT) #$(EXIT) #$(RENDER)