#ifndef STR_H
#define STR_H

#include "SDL/SDL.h"

struct str_col {
	int *discCol;
	int nbDiscCol;
	SDL_Rect socle;
};

struct str_disc {
	int x;
	SDL_Rect rect;
};

#endif
