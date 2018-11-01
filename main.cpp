#include <iostream>
#include <string>
#include "Display.h"

using namespace std;

int ch_to_int(char *ch);

int main(int argc,char **argv) {

	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *ecran=SDL_SetVideoMode(1000, 400, 32, 0);
	SDL_Surface *text=NULL;
	SDL_WM_SetCaption("Hanoi", NULL);
	SDL_FillRect(ecran, NULL,0x57330e);
	SDL_Event event;
	int stop=0;
	int y;
	int nbDisc=3;
	int nbCol=3;

	for (y=1;y<argc;y++){
		if (argv[y][0]=='-'){
			switch (argv[y][1]){
				case 'd':{
					nbDisc=ch_to_int(argv[y]);
				}break;
				case 'c':{	
					nbCol=ch_to_int(argv[y]);
				}break;
			}
		}
	}

	class Plateau plateau(nbDisc,nbCol);
	Display(ecran,plateau,nbDisc,nbCol);

	while (!stop){
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT){
			stop=1;
		}
		else if (event.type==SDL_KEYDOWN){
			if (event.key.keysym.sym>=SDLK_KP1 && event.key.keysym.sym-SDLK_KP1<nbCol){
				plateau.human_deplacement(plateau,event.key.keysym.sym-SDLK_KP1,ecran,event);
			}
			else {
				switch (event.key.keysym.sym){	
					case SDLK_ESCAPE:{
						plateau.dlete();
						stop=1;
						break;
					}
					case SDLK_r:{
						plateau.reset();
						Display(ecran,plateau,nbDisc,nbCol);
						break;
					}
					case SDLK_d:{
						int spd=1;
						SDL_WaitEvent(&event);
						if (event.type==SDL_KEYDOWN){
							if (event.key.keysym.sym>=SDLK_KP1 && event.key.keysym.sym<=SDLK_KP9){
								spd=event.key.keysym.sym-SDLK_KP0;
							}
						}
						plateau.do_it(plateau,ecran,spd);
						Display(ecran,plateau,nbDisc,nbCol);
						break;
					}
				}
			}
		}
	}
	TTF_Quit();
	SDL_Quit();
return 0;
}

int ch_to_int(char *ch){
	
	int i;
	int numb=0;
	
	for (i=2;ch[i]>='0' && ch[i]<='9';i++){
		numb=10*numb+ch[i]-'0';
	}

return numb;
}
