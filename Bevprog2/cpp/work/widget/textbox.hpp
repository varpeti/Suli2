#ifndef _TEXTBOX_	//ujabb definíció és fordítási hiba elkerülésére
#define _TEXTBOX_

#include "stattext.hpp"

class TEXTBOX : public STATTEXT
{
	protected:

	unsigned int size;

	public:

	TEXTBOX(double x, double y, unsigned int size, SZIN szin, SZIN szin2, string szoveg="")
		: STATTEXT(x,y,szin,szin2,szoveg), size(size)
	{
		sx=gout.twidth("A")*(size)+TEXT_RAHAGYAS;
	}

	virtual void srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const;
	virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
};

bool TEXTBOX::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	
	if (ev.type==ev_key)
	{
		if (ev.keycode>31) szoveg+=ev.keycode; // Írás
		else if (ev.keycode==key_backspace) szoveg = szoveg.substr(0, szoveg.size()-1); // Törlés

		if (szoveg.size()>(size-1)) szoveg = szoveg.substr(0, szoveg.size()-1); // Nincs több karakter hely
		return true; // Elfogja a karaktereket.
	}
	return false;
}

void TEXTBOX::srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const
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

	SZIN rszin = (focus ? szin2 : szin);
	SZIN rszin2 = (focus ? szin : szin2);

	gout << color(rszin.rr,rszin.gg,rszin.bb) << move_to(ux,uy) << box(usx,usy);
	/*string ki = szoveg;
	while (usx<gout.twidth(ki)) // Mindig a szöveg vége veszik el.
	{
		ki = ki.substr(0, ki.size()-1);
	}
	gout << color(rszin2.rr,rszin2.gg,rszin2.bb) << move_to(ux,uy+gout.cascent()) << text(ki);*/
	canvas c;
	c.open(462,462);
	c.transparent(true);

	string ki = szoveg;
	c << color(rszin2.rr,rszin2.gg,rszin2.bb) << move_to(0,0+gout.cascent()) << text(ki);
	ux=x+X0; uy=y+Y0;
	kamera.getKamCoords(ux,uy);
	gout << stamp(c,ux,uy);
}


#endif