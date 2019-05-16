#ifndef _MENU_
#define _MENU_

#include "ablak.hpp"

class MENU : public ABLAK
{
	private:
		int kattintva;
	public:

		MENU(double x, double y, double sx, double spacey, unsigned int kx, unsigned int ky, vector<OBJ*> objs, bool mozgathato=true)
			: ABLAK(x,y,sx,0,kx,ky,mozgathato)
		{	
			int holy = spacey;
			for (int i = 0; i < objs.size(); ++i)
			{
				objektumok.push_back(objs[i]);
				double osx,osy;
				objs[i]->getMeret(osx,osy);
				objs[i]->setPosition(sx/2-osx/2,holy);
				holy+=osy+spacey;
			}
			sy=holy;
			kattintva=0;

		}

		bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
		void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat, utólag.
		void getter(ostream& ki) const;
};

bool MENU::supdate(event ev, double X0, double Y0, KAMERA kamera)
{

	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
		{
			double ux,uy; // Kamera elmozdulás miatt kellenek.
			ux=x+X0;uy=y+Y0;
			kamera.getKamCoords(ux,uy);
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {
					kattintva=i+1;
					return true;
				}
			}
			kattintva=0;
		}
	}
	return false;
}

void MENU::getter(ostream& ki) const 
{
	ki << kattintva;
}

class MENUPONT : public ABLAK
{
public:
	MENUPONT(double sx, double sy, unsigned int kx, unsigned int ky) 
		: ABLAK(0,0,sx,sy,kx,ky,false) 
	{};
	~MENUPONT();
	
};

#endif