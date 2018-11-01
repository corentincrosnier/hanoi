#ifndef PLATEAU_H
#define PLATEAU_H

#include "str.h"
#include <math.h>
#include <SDL/SDL_ttf.h>

class Plateau{
	public:
		
	Plateau(int nbDisc,int nbCol);
	void do_it(Plateau plateau, SDL_Surface *ecran,int spd);
	void reset();
	void dlete();
	bool verif();
	int f_col(int nCol);
	void rotate(int sense);
	void exchange(int sens);
	void set_rect(int nDisc,int x,int y,int h,int w);
	void set_socle(int nCol,int x,int y,int h,int w);
	void set_discCol(int nCol,int nv_disc);
	SDL_Rect* get_rect(int nDisc);
	SDL_Rect* get_socle(int nCol);
	SDL_Rect* get_base();
	int get_discCol(int nCol);
	int get_nbDisc();
	int get_nbCol();
	void Dbt_deplacement(Plateau plateau,int nCol,SDL_Surface *ecran);
	void bot_deplacement(Plateau plateau,int dbt_col,int f_col,SDL_Surface *ecran,int spd);
	void human_deplacement(Plateau plateau,int nCol,SDL_Surface *ecran,SDL_Event event);
	
	protected:
	
	int m_nbCoup;
	int m_nbDisc;
	int m_nbCol;
	int newnit[7];
	int sub_unit[7];
	SDL_Rect base;
	TTF_Font *m_font;
	str_disc *disc;
	str_col *col;
};

#endif
