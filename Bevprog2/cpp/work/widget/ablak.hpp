#ifndef _ABLAK_	//ujabb definíció és fordítási hiba elkerülésére
#define _ABLAK_

#define ABLAK_RAHAGYAS 5

#include "szin.hpp"
#include "env.hpp"

using namespace genv;

class ABLAK : public OBJ
{
	protected:

	SZIN szin; //szín
	unsigned int kx,ky; // kép x,y

	public:

	ABLAK(double x, double y, double sx, double sy, unsigned int kx, unsigned int ky, bool mozgathato=true)
		:  OBJ(x,y,sx,sy,mozgathato), kx(kx), ky(ky)
	{
		szin = SZIN(0,0,0);
	}
	ABLAK(double x, double y, double sx, double sy, SZIN szin, bool mozgathato=true)
		: OBJ(x,y,sx,sy,mozgathato), szin(szin)
	{
		kx=9876; // Minek definiáljak -1-et? unsigned és ekkora képet nem tudna beolvasni.
		ky=9876;
	}

	virtual void srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const;
	virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera);
	virtual void getter(ostream& ki) const;
};

void ABLAK::srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x+X0;uy=y+Y0;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getKamCoords(ux,uy);
	if (ux+usx<Xb or ux>Xb+Xj or uy+usy<Yb or uy>Yb+Yj) return;
	if (ux+usx>Xb+Xj) {usx=Xb+Xj-ux;}
	if (ux<Xb) {usx+=ux-Xb; ukx-=ux; ux=Xb;}
	if (uy+usy>Yb+Yj) {usy=Yb+Yj-uy;}
	if (uy<Yb) {usy+=uy-Yb; uky-=uy; uy=Yb;}

	if (kx==9876 and ky==9876)
		gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy); // szín
	else 
		gout << stamp(Tkepek,ukx,uky,usx,usy,ux,uy); // Kép
	
	for (int i = 0; i < objektumok.size();++i) // Saját objektumai kirajzolása
	{
		objektumok[i]->srajzol(Tkepek,x+X0,y+Y0,ux,uy,usx,usy,kamera,(i+1==objektumok.size()&&focus)); // Ha utolsó elem és az ablak is az utolsó: focusban van.
	}
}

bool ABLAK::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (objektumok.size()==0) return false; // Ha nincs benne semmi, az alatta lévők mozognak.

	double ux,uy,uX0,uY0; // Kamera elmozdulás miatt kellenek.
	ux=x+X0;uy=y+Y0;
	uX0=X0;uY0=Y0;

	if (objektumok[objektumok.size()-1]->supdate(ev,ux,uy,kamera)) return true; // Ha benne lévőt mozgattnak nem mozognak visszamenőleg.

	kamera.getKamCoords(ux,uy);
	kamera.getKamCoords(uX0,uY0);

	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
			for (int i = objektumok.size()-1; i >= 0; i--)
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy) and this->BenneVan(ev.pos_x-uX0,ev.pos_y-uY0)) // Az egér a belsőre kattint, mozgatható a belső, és a külsőben is benne van az egér
				{
					if (objektumok[i]->isMozgathato())
					{
						objektumok[i]->getPosition(ex,ey);
						ex-=ev.pos_x;
						ey-=ev.pos_y;
						lenyomva=true;
					}
					ObjKiemel(objektumok[i]);
					break;
				}
		if (-ev.button==btn_left) {lenyomva=false; ex=0; ey=0;} // Ha felengedi
		

		if (lenyomva) {
			double lx,ly,lsx,lsy;
			objektumok[objektumok.size()-1]->getMeret(lsx,lsy);
			lx=ev.pos_x+ex;
			ly=ev.pos_y+ey;
			if (!(lx+lsx<ABLAK_RAHAGYAS or lx>sx-ABLAK_RAHAGYAS or ly+lsy<ABLAK_RAHAGYAS or ly>sy-ABLAK_RAHAGYAS)) objektumok[objektumok.size()-1]->setPosition(lx,ly); // ameddig nyomva van, és benne van a külsőben mozog.
		}
	}
	return lenyomva;
}

void ABLAK::getter(ostream& ki) const
{
	ki << objektumok[objektumok.size()-1]; // A fókuszban lévő objektum memória címét adja vissza.
}

#endif