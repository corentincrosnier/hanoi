#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h>
#include "Plateau.h"
#include <SDL/SDL_ttf.h>

void Display(SDL_Surface *ecran,Plateau plateau,int nbDisc,int nbCol);
void Disp_nbCoup(SDL_Surface *ecran,TTF_Font *font,int nbCoup);
char* int_to_ch(int numb);

#endif
