RENDER= render.c

#EXIT= exit/utils.c

PARSER= parsing/found_utils.c parsing/validate_textures.c \
	parsing/validate_map.c \
	parsing/utils.c parsing/validate_rgb.c \
	parsing/map_check.c parsing/map_utils.c

FILES = main.c $(PARSER) #$(EXIT) #$(RENDER)