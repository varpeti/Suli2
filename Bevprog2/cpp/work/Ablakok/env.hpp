#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "graphics.hpp"
#include "sstream"
#include "fstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "kamera.hpp"
#include "iostream"
#include "algorithm"

using namespace genv;
using namespace std;

/* DEKRALÁCIÓK	*/

struct SZIN
{
	char rr,gg,bb;

	SZIN(char rr,char gg,char bb) : rr(rr), gg(gg), bb(bb) {};

	SZIN() : rr(0), gg(0), bb(0) {};
};


/* CLASS 	*/

class ENV
{
	protected:

	canvas TSPRITEOK;	//az összes sprite képét ide olvasom be

	unsigned int KEPERNYOSZELESSEG;
	unsigned int KEPERNYOMAGASSAG;

	public:

	// mezők;
	event ev;
	KAMERA kamera;

	//konst dest
	ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
	ENV(unsigned int szelesseg, unsigned int magassag);
	~ENV();

	// tagfüggvények
	void kirajzol();
	bool spriteok_beolvas(const char *fname); // BMP-ből olvassa be az összes spriteot

	class SPRITE
	{
		protected:

		double x,y; // kooridiáták lehet negatív is
		char allapot; // 255 törölhető, 0 látszik updetelődik, 1 lát, 2 update, else semmi
		double sx,sy; // szélesség magasság
		SZIN szin; //szín
		unsigned int kx,ky; // sprite x,y
		double vx,vy; // sebesség
		SPRITE *utk;

		public:

		SPRITE(double x,double y,unsigned int allapot, unsigned int kx, unsigned int ky, double sx, double sy)
			: x(x), y(y), allapot(allapot), kx(kx), ky(ky), sx(sx), sy(sy)
		{
			szin = SZIN(0,0,0);
			vx=0;
			vy=0;
			utk=NULL;
		}
		SPRITE(double x,double y,unsigned int allapot,double sx, double sy,SZIN szin)
			: x(x), y(y), allapot(allapot), sx(sx), sy(sy), szin(szin)
		{
			kx=0;
			ky=0;
			vx=0;
			vy=0;
			utk=NULL;
		}

		virtual void srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera);
		virtual void supdate(vector<SPRITE*> &SPRITEOK);

		// Azért nem hülyeség a getter és setter mert SEXYBB mint a mezők :D | Egyébként az adatok főleg párosával vannak.
		void setSebesseg(double vx,double vy);
		void getSebesseg(double &vx,double &vy);
		void setPosition(double x,double y);
		void getPosition(double &x,double &y);
		void setAllapot(char allapot);
		int  getAllapot();
		void setMeret(double sx,double sy);
		void getMeret(double &sx,double &sy);


		bool BenneVan(double px, double py);
		SPRITE *utkozott();

	};

	vector<SPRITE*> SPRITEOK; // Az összes sprite

	SPRITE *newSprite(double x, double y, unsigned int kx, unsigned int ky, double sx, double sy); // spriteos
	SPRITE *newSprite(double x, double y, double sx, double sy,SZIN szin); // színes
	void SpriteKiemel(SPRITE *sp); // Előre hozza a spriteot.
};

/* MEGVALÓSÍTÁS */

//konst

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
}

ENV::~ENV() //dest
{

}

ENV::SPRITE *ENV::newSprite(double x, double y, unsigned int kx, unsigned int ky, double sx, double sy)
{
	SPRITE *sp = new SPRITE(x,y,0,kx,ky,sx,sy);
	SPRITEOK.push_back(sp);
	return sp;
}

ENV::SPRITE *ENV::newSprite(double x, double y, double sx, double sy, SZIN szin)
{
	SPRITE *sp = new SPRITE(x,y,0,sx,sy,szin);
	SPRITEOK.push_back(sp);
	return sp;
}

void ENV::SpriteKiemel(ENV::SPRITE *sp)
{
	for (int i = 0; i < SPRITEOK.size(); ++i)
		if (SPRITEOK[i]==sp)
		{
			SPRITEOK.push_back(sp);
			SPRITEOK.erase(SPRITEOK.begin()+i);
			return;
		}
}

void ENV::kirajzol()
{
	gout << color(0,0,0) << move_to(0,0) << box(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);

	for (int i = 0; i < SPRITEOK.size();)
	{
		if (SPRITEOK[i]->getAllapot()==0 or SPRITEOK[i]->getAllapot()==2) SPRITEOK[i]->supdate(SPRITEOK);
		if (SPRITEOK[i]->getAllapot()==0 or SPRITEOK[i]->getAllapot()==1) SPRITEOK[i]->srajzol(TSPRITEOK,KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,kamera);
		if (SPRITEOK[i]->getAllapot()==255)
		{ //törlés
			delete SPRITEOK[i];
			SPRITEOK[i] = SPRITEOK[SPRITEOK.size()-1];
			SPRITEOK.pop_back();
		}
		else ++i; // Ha nem törlődik, a következőre lép
	}

	gout << refresh;
}

void ENV::SPRITE::srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera)
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x;uy=y;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getCoords(ux,uy);
	if (ux+usx<0 or ux>KEPERNYOSZELESSEG or uy+usy<0 or uy>KEPERNYOMAGASSAG) return;
	if (ux+usx>KEPERNYOSZELESSEG) {usx=KEPERNYOSZELESSEG-ux;}
	if (ux<0) {usx+=ux; ukx-=ux; ux=0;}
	if (uy+usy>KEPERNYOMAGASSAG) {usy=KEPERNYOMAGASSAG-uy;}
	if (uy<0) {usy+=uy; uky-=uy; uy=0;}
	if (kx==0 and ky==0) 
		gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy); // szín
	else 
		gout << stamp(TS,ukx,uky,usx,usy,ux,uy); // A canvasra nem lehet stampelni? ezért így van megoldva a "kilógás"
}

void ENV::SPRITE::supdate(vector<SPRITE*> &SPRITEOK)
{
	x+=vx;
	y+=vy;
	utk = NULL;

	auto bennevan = [](double px, double py, double mx, double my, int msx, int msy) 
	{ 
		if (px>=mx and px<=mx+msx and py>=my and py<=my+msy) return true;
		return false;
	};

	for (int i = 0; i < SPRITEOK.size(); ++i)
		if ( (SPRITEOK[i]->allapot==0 or SPRITEOK[i]->allapot==2) and SPRITEOK[i]!=this)
		{
			if (bennevan(x,y,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or bennevan(x+sx,y,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or bennevan(x,y+sy,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or bennevan(x+sx,y+sy,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or
				bennevan(SPRITEOK[i]->x,SPRITEOK[i]->y,x,y,sx,sy) or bennevan(SPRITEOK[i]->x+SPRITEOK[i]->sx,SPRITEOK[i]->y,x,y,sx,sy) or bennevan(SPRITEOK[i]->x,SPRITEOK[i]->y+SPRITEOK[i]->sy,x,y,sx,sy) or bennevan(SPRITEOK[i]->x+SPRITEOK[i]->sx,SPRITEOK[i]->y+SPRITEOK[i]->sy,x,y,sx,sy)) 
				{utk=SPRITEOK[i];}
		}
}

void ENV::SPRITE::setSebesseg(double uvx,double uvy)
{
	vx=uvx;
	vy=uvy;
}

void ENV::SPRITE::getSebesseg(double &uvx,double &uvy)
{
	uvx=vx;
	uvy=vy;
}

void ENV::SPRITE::setPosition(double ux,double uy)
{
	x=ux;
	y=uy;
}

void ENV::SPRITE::getPosition(double &ux,double &uy)
{
	ux=x;
	uy=y;
}

void ENV::SPRITE::setAllapot(char uallapot)
{
	if (uallapot>3 or uallapot<0 or uallapot!=255) return;
	allapot=uallapot;
}

int ENV::SPRITE::getAllapot()
{
	return allapot;
}

void ENV::SPRITE::setMeret(double usx,double usy)
{
	sx=usx;
	sy=usy;
}

void ENV::SPRITE::getMeret(double &usx,double &usy)
{
	usx=sx;
	usy=sy;
}


ENV::SPRITE *ENV::SPRITE::utkozott()
{
	return utk;
}

bool ENV::SPRITE::BenneVan(double px, double py)
{
	if (px>=x and px<=x+sx and py>=y and py<=y+sy) return true;
	return false;
};


bool ENV::spriteok_beolvas(const char *fname) // CSAK azért is BMPből.
{
	/*
	ifstream be(fname);
	if (!be.is_open()) return;
	int kx,ky;
	be >> kx;
	be >> ky;
	TSPRITEOK.open(kx,ky); //TSPRITEOK.load_font("font.ttf",12,true);
	for (int i = 0; i < ky; ++i)
	{
		for (int j = 0; j < kx; ++j)
		{
			int rr; be >> rr;
			int gg; be >> gg;
			int bb; be >> bb;
			TSPRITEOK << move_to(j,i) << color(rr,gg,bb) << dot;
		}
	}
	be.close();*/

	FILE* f = fopen(fname, "rb"); if (!f) return false;
	char info[54] = {0}; // 54 byte: az infók
	fread(info, sizeof(char), 54, f); 

	unsigned int width = *(int*)&info[18]; //18. szélesség
	unsigned int height = *(int*)&info[22]; //22. magasság

	unsigned int size = 3 * width * height; // 3 byte pixelenként
	char* data = new char[size]; // lefoglalás
	fread(data, sizeof(char), size, f); // beolvasás egyszerre / csak ha nincsenek színtérinformációk, különben csúszik
	fclose(f);

	TSPRITEOK.open(width,height); // canvas megnyitása
	unsigned int k = 0;
	for (unsigned int i = 0; i < height; i++) //y
	{
		for (unsigned int j = 0; j < width; j++) //x
		{
			unsigned int bb = data[k]; k++; // Igen a mikrofos BBGGRR formátumot használ
			unsigned int gg = data[k]; k++;
			unsigned int rr = data[k]; k++;
			TSPRITEOK << move_to(j,height-i) << color(rr,gg,bb) << dot; // ja és fejjel lefele (MIÉRT???)
		}
	}
	delete data; //Nem használt memória felszabadítása
	return true;
}

#endif