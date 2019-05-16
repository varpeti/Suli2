#ifndef _MM_
#define _MM_

#include "textbox.hpp"

class MM : public ABLAK
{
	int kattintva;

	public:

		MM(double x, double y, unsigned int kx, unsigned int ky, bool mozgathato=true)
			: ABLAK(x,y,10*10*5,0,kx,ky,mozgathato)
		{	
			int holy = ABLAK_RAHAGYAS;
			for (int i = 0; i < 8; ++i)
			{
				OBJ *gomb = new ABLAK(0,0,10,10,SZIN(0,0,255));
				OBJ *doboz = new TEXTBOX(0,0,10,SZIN(0,0,1),SZIN(200,200,0));
				objektumok.push_back(doboz);
				objektumok.push_back(gomb);
				double osx,osy;
				doboz->getMeret(osx,osy);
				doboz->setPosition(sx/5-osx/2,holy);
				gomb->setPosition(sx/5+osx/2+ABLAK_RAHAGYAS,holy+3);
				holy+=osy+ABLAK_RAHAGYAS;
			}
			sy=holy;
			kattintva=-1;
		}

		bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
		void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat, utólag.
		void getter(ostream& ki) const;
};

bool MM::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	double ux,uy,uX0,uY0; // Kamera elmozdulás miatt kellenek.
	ux=x+X0;uy=y+Y0;
	uX0=X0;uY0=Y0;

	if (objektumok[objektumok.size()-1]->supdate(ev,ux,uy,kamera)) return true; // Ha benne lévőt mozgattnak nem mozognak visszamenőleg.

	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
		{
			kamera.getKamCoords(ux,uy);
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {
					if (i%2==1)
					{
						delObj(objektumok[i]);
					}
					else
					{
						kattintva=i;
					}
					return true;
				}
			}
		}
	}
	return false;
}

void MM::getter(ostream& ki) const 
{
	ki << kattintva;
}

#endif