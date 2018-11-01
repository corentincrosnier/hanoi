#include <iostream>
#include <math.h>
#include "Display.h"

using namespace std;

void Display(SDL_Surface *ecran,Plateau plateau,int nbDisc,int nbCol){
	int i;
	SDL_FillRect(ecran, NULL,0x57330e);
	for (i=0;i<nbCol;i++){
		SDL_FillRect(ecran,plateau.get_socle(i),0xffffff);
	}
	for (i=0;i<nbDisc;i++){
		SDL_FillRect(ecran,plateau.get_rect(i),0xf7bd36);
	}
	SDL_FillRect(ecran,plateau.get_base(),0xffffff);
	SDL_UpdateRect(ecran,0,0,0,0);
}

void Disp_nbCoup(SDL_Surface *ecran,TTF_Font *font,int nbCoup){
	SDL_Color color={150,20,60};
	SDL_Rect position;

	position.x=0;
	position.y=0;
	SDL_Surface *text=TTF_RenderText_Solid(font,int_to_ch(nbCoup),color);
	SDL_BlitSurface(text,NULL,ecran,&position);
}

char* int_to_ch(int numb){
	int i;
	int a=log10(numb)+1;
	cout << a << endl;
	char *txt;
	txt=new char[a+1];

	for(i=0;i<a;i++){
		txt[i]=(char)((int)('0'+(numb/pow(10,a-i-1))));
		numb-=pow(10,a-i-1);
	}
	txt[a]='\0';

return txt;
}
