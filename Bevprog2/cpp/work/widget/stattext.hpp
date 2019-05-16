#ifndef _STATTEXT_	//ujabb definíció és fordítási hiba elkerülésére
#define _STATTEXT_

#define TEXT_RAHAGYAS 2

#include "ablak.hpp"


using namespace genv;

class STATTEXT : public ABLAK
{
	protected:

	string szoveg;
	SZIN szin2;

	public:

	STATTEXT(double x, double y, SZIN szin, SZIN szin2, string szoveg)
		: ABLAK(x,y,gout.twidth(szoveg)+TEXT_RAHAGYAS,gout.cascent()+TEXT_RAHAGYAS*2,szin,false), szin2(szin2), szoveg(szoveg)
	{}

	virtual void srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const;
	virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera) {}; 
	virtual void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat.
	virtual void getter(ostream& ki) const; // Kiírja az értékét, menünél / textboxnál kell majd.
	virtual void setter(istream& be); // Menükiemeléshez kell majd.
};

void STATTEXT::srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x+X0;uy=y+Y0;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getKamCoords(ux,uy);
	//if (ux+usx<Xb or ux>Xb+Xj or uy<Yb or uy+usy>Yb+Yj) return; // Akkor is kilép ha felül vagy alul kilógna.
	if (ux+usx<Xb or ux>Xb+Xj or uy+usy<Yb or uy>Yb+Yj) return;
	if (ux+usx>Xb+Xj) {usx=Xb+Xj-ux;}
	if (ux<Xb) {usx+=ux-Xb; ukx-=ux; ux=Xb;}
	if (uy+usy>Yb+Yj) {usy=Yb+Yj-uy;}
	if (uy<Yb) {usy+=uy-Yb; uky-=uy; uy=Yb;} 

	gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy);
	/*string ki = szoveg;
	while (usx<gout.twidth(ki)) // Mindig a szöveg vége veszik el.
	{
		ki = ki.substr(0, ki.size()-1);
	}
	gout << color(szin2.rr,szin2.gg,szin2.bb) << move_to(ux,uy+gout.cascent()) << text(ki);*/

	canvas c;
	c.open(462,462);
	c.transparent(true);

	string ki = szoveg;
	c << color(szin2.rr,szin2.gg,szin2.bb) << move_to(0,0+gout.cascent()) << text(ki);
	ux=x+X0; uy=y+Y0;
	kamera.getKamCoords(ux,uy);
	gout << stamp(c,ux,uy);
}

void STATTEXT::getter(ostream& ki) const 
{
	ki << szoveg;
};

void STATTEXT::setter(istream& be)
{
	SZIN seged = szin;
	szin = szin2;
	szin2 = seged;
}

#endif