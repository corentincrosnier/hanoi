#include <iostream>
#include <unistd.h>
#include "Plateau.h"
#include "Display.h"

using namespace std;



Plateau::Plateau(int nbDisc,int nbCol){
	int i,r;
	m_font=TTF_OpenFont("./Amatic-Bold.ttf",30);
	m_nbCoup=0;
	m_nbDisc=nbDisc;
	m_nbCol=nbCol;
	disc=new str_disc[m_nbDisc];
	col=new str_col[m_nbCol];
	for (i=0;i<nbDisc;i++){
		disc[i].x=0;
		disc[i].rect.x=static_cast<int>(25+(230/((nbDisc-1)*2))*(nbDisc-(i+1)));
		disc[i].rect.y=static_cast<int>(200+i*(200/nbDisc));
		disc[i].rect.h=static_cast<int>(200/nbDisc);
		disc[i].rect.w=static_cast<int>(300-(230/(nbDisc-1))*(nbDisc-(i+1)));
	}
	for (i=0;i<nbCol;i++){
		col[i].discCol=new int[nbDisc];
		for (r=0;r<nbDisc;r++){
			if (i==0){
				col[i].discCol[r]=r;
				col[i].nbDiscCol=m_nbDisc;
			}
			else{
				col[i].discCol[r]=-1;
				col[i].nbDiscCol=0;
			}
		}
		col[i].socle.x=static_cast<int>((900/(nbCol*2)+25)+i*((900/nbCol)+25)-15);
		col[i].socle.y=150;
		col[i].socle.h=250;
		col[i].socle.w=31;
	}
	for (i=0;i<7;i++){
		if (i==4 || i==5){
			sub_unit[i]=1;
		}
		else {
			sub_unit[i]=0;
		}
	}
	sub_unit[2]=2;
	exchange(-1);
	base.x=0;
	base.y=200+m_nbDisc*disc[0].rect.h;
	base.h=200-m_nbDisc*disc[0].rect.h;;
	base.w=1000;
}

void Plateau::do_it(Plateau plateau, SDL_Surface *ecran, int spd){
	int i,r;
	int p=1;
	int k=0;

	if (verif()){
		for (r=0;r<pow(2,m_nbDisc-3);r++){
			if (m_nbDisc%2==0){
				exchange((r+p)%3);
				p++;
			}
			else {
				rotate((r+2)%3);
			}
			for (i=0;i<7;i++){
					bot_deplacement(plateau,newnit[i],f_col(newnit[i]),ecran,spd);
					cout << newnit[i];
			}
			if (r!=pow(2,m_nbDisc-3)-1){
				if (m_nbDisc%2){
					k+=!(r%7);
					exchange(((r/7)+k)%3);
				}
				else {
					rotate((r/7+2)%3);
				}
				cout << "m=" << newnit[r%7] << endl;
				bot_deplacement(plateau,newnit[r%7],f_col(newnit[r%7]),ecran,spd);
			}
		}
	}
}

void Plateau::reset(){
	int i,r;

	for (i=0;i<m_nbDisc;i++){
		disc[i].x=0;
		disc[i].rect.x=static_cast<int>(25+(230/((m_nbDisc-1)*2))*(m_nbDisc-(i+1)));
		disc[i].rect.y=static_cast<int>(200+i*(200/m_nbDisc));
		disc[i].rect.h=static_cast<int>(200/m_nbDisc);
		disc[i].rect.w=static_cast<int>(300-(230/(m_nbDisc-1))*(m_nbDisc-(i+1)));
	}
	for (i=0;i<m_nbCol;i++){
		for (r=0;r<m_nbDisc;r++){
			if (i==0){
				col[i].discCol[r]=r;
			}
			else{
				col[i].discCol[r]=-1;
			}
		}
		col[i].socle.x=static_cast<int>((900/(m_nbCol*2)+25)+i*((900/m_nbCol)+25)-15);
		col[i].socle.y=150;
		col[i].socle.h=250;
		col[i].socle.w=31;
		col[i].nbDiscCol=((i==0)?m_nbDisc:0);
		m_nbCoup=0;
	}
}

void Plateau::dlete(){
	delete[] disc;
	delete[] col;
	TTF_CloseFont(m_font);
}

bool Plateau::verif(){
	bool verif=false;

	if (col[0].nbDiscCol==m_nbDisc){
		if(m_nbCol==3){
			verif=true;
		}
	}

return verif;
}

int Plateau::f_col(int nCol){
	int f_col;
	
	if (col[nCol].nbDiscCol%2==1){
		f_col=((nCol==2)?1:2);
	}
	else {
		f_col=((nCol==0)?1:0);
	}

return f_col;
}

void Plateau::rotate(int sens){
	int i;

	for (i=0;i<7;i++){
		newnit[i]=sub_unit[i];
		if (sens==1){
			newnit[i]=(sub_unit[i]+1)%3;
		}
		else if(sens==0){
			newnit[i]=((sub_unit[i]==0)?2:sub_unit[i]-1);
		}
	}
}

void Plateau::exchange(int sens){
	int i;

	for (i=0;i<7;i++){
		newnit[i]=sub_unit[i];
		if (sens>=0) {
			if (sub_unit[i]==sens){
				newnit[i]=(sens+1)%3;
			}
			else if(sub_unit[i]==(sens+1)%3) {
				newnit[i]=sens;
			}
		}
	}
}

void Plateau::set_rect(int nDisc,int x,int y,int h,int w){
	disc[nDisc].rect.x+=x;
	disc[nDisc].rect.y+=y;
	disc[nDisc].rect.h+=h;
	disc[nDisc].rect.w+=w;
}

void Plateau::set_socle(int nCol,int x,int y,int h,int w){
	col[nCol].socle.x+=x;
	col[nCol].socle.y+=y;
	col[nCol].socle.h+=h;
	col[nCol].socle.w+=w;
}

void Plateau::set_discCol(int nCol,int nv_disc){
	int i;
	for (i=0;i<m_nbDisc;i++){
		if (nv_disc==-1){
			if (col[nCol].discCol[i]!=-1){
				col[nCol].discCol[i]=-1;
				break;
			}
		}
		else {
			if (col[nCol].discCol[i]!=-1){
				col[nCol].discCol[i-1]=nv_disc;
				break;
			}
			else if (col[nCol].discCol[m_nbDisc-1]==-1){
				col[nCol].discCol[m_nbDisc-1]=nv_disc;
				break;
			}
		} 
	}
}

SDL_Rect* Plateau::get_rect(int nDisc){
return &disc[nDisc].rect; 
} 

SDL_Rect* Plateau::get_socle(int nCol){
return &col[nCol].socle; 
} 

SDL_Rect* Plateau::get_base(){
return &base;
}

int Plateau::get_discCol(int nCol){
	int i;
	int rtn=-1;
	for (i=0;i<m_nbDisc;i++){
		if (col[nCol].discCol[i]!=-1){
			rtn=col[nCol].discCol[i];
			break;
		}
	}
return rtn;
}

int Plateau::get_nbDisc(){
return m_nbDisc;
}

int Plateau::get_nbCol(){
return m_nbCol;
}

void Plateau::Dbt_deplacement(Plateau plateau,int nCol,SDL_Surface *ecran){
	int i;
	int nDisc=plateau.get_discCol(nCol);
	int up_value=100;

	for (i=0;i<m_nbDisc;i++){
		if (col[nCol].discCol[i]==nDisc){
			break;
		}
	}
	up_value+=i*disc[0].rect.h;
	plateau.set_rect(nDisc,0,-up_value,0,0);
	plateau.set_discCol(nCol,-1);
	col[nCol].nbDiscCol--;
	Display(ecran,plateau,m_nbDisc,m_nbCol);
}

void Plateau::bot_deplacement(Plateau plateau,int dbt_col,int f_col,SDL_Surface *ecran,int spd){
	int i;
	int nDisc=plateau.get_discCol(dbt_col);
	int down_value=100-disc[nDisc].rect.h;

	plateau.Dbt_deplacement(plateau,dbt_col,ecran);
	usleep(500000/spd);
	plateau.set_rect(nDisc,(f_col-dbt_col)*325,0,0,0);
	Display(ecran,plateau,m_nbDisc,m_nbCol);
	usleep(500000/spd);
	disc[nDisc].x=f_col;
	for (i=0;i<m_nbDisc;i++){
		if (col[f_col].discCol[i]==-1){
			down_value+=disc[nDisc].rect.h;
		}
		else {
			break;
		}
	}
	plateau.set_discCol(f_col,nDisc);
	plateau.set_rect(nDisc,0,down_value,0,0);
	col[f_col].nbDiscCol++;
	Display(ecran,plateau,m_nbDisc,m_nbCol);
}

void Plateau::human_deplacement(Plateau plateau,int nCol,SDL_Surface *ecran,SDL_Event event){
	int stop=0;
	int nDisc=plateau.get_discCol(nCol);
	int f_col=nCol;

	if (nDisc!=-1){
		plateau.Dbt_deplacement(plateau,nCol,ecran);
	}
	else {
		stop=1;
	}
	while (!stop){
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYDOWN){
			switch (event.key.keysym.sym){
				case SDLK_LEFT:
					if (disc[nDisc].x>0){
						plateau.set_rect(nDisc,-325,0,0,0);
						disc[nDisc].x+=-1;
						Display(ecran,plateau,m_nbDisc,m_nbCol);
						f_col--;
					}
					break;
				case SDLK_RIGHT:
					if (disc[nDisc].x<m_nbCol-1){
						plateau.set_rect(nDisc,325,0,0,0);
						disc[nDisc].x+=1;
						Display(ecran,plateau,m_nbDisc,m_nbCol);
						f_col++;
					}
					break;
				case SDLK_DOWN:
					int i;
					int down_value=100-disc[nDisc].rect.h;
					if (plateau.get_discCol(f_col)>nDisc || plateau.get_discCol(f_col)==-1){
						for (i=0;i<m_nbDisc;i++){
							if (col[f_col].discCol[i]==-1){
								down_value+=disc[nDisc].rect.h;
								m_nbCoup++;
							}
							else {
								break;
							}
						}
					}
					else {
						break;
					}
					plateau.set_discCol(f_col,nDisc);
					plateau.set_rect(nDisc,0,down_value,0,0);
					col[f_col].nbDiscCol++;
					Display(ecran,plateau,m_nbDisc,m_nbCol);
					Disp_nbCoup(ecran,m_font,m_nbCoup);
					SDL_UpdateRect(ecran,0,0,0,0);
					stop=1;
			}
		}	
	}
}

/*void mid(int newnit,int p)
{
	if(!p)
		return x;
	else
		return x*pow(x, p-1);
}
0753616676*/
