#ifndef _KIVALASZTO_	//ujabb definíció és fordítási hiba elkerülésére
#define _KIVALASZTO_

#include "textbox.hpp"

using namespace genv;

class KIVALASZTO : public ABLAK
{
	private:
		unsigned int size,size2; // Azért kellenek hogy újat lehessen hozzáadni.
		SZIN szin2;
		int kivalasztva;
	public:

		KIVALASZTO(double x, double y, SZIN szin, SZIN szin2, vector<string> lista, unsigned int size2=0,unsigned int size=8)
			: ABLAK(x,y,gout.twidth("A")*size+TEXT_RAHAGYAS*3,
				(gout.cascent()+TEXT_RAHAGYAS*4)*( (size2 ? size2 : lista.size()) +2)+TEXT_RAHAGYAS,
				szin2,false), szin2(szin), size(size), size2(size2)
		{	
			string gorget;
			while (gorget.size()<size) gorget+='-';
			objektumok.push_back( new STATTEXT(TEXT_RAHAGYAS,TEXT_RAHAGYAS,szin,szin2,gorget) );
			objektumok.push_back( new STATTEXT(TEXT_RAHAGYAS,TEXT_RAHAGYAS+(gout.cascent()+TEXT_RAHAGYAS*4)*(lista.size()+1),szin,szin2,gorget) );
			for (int i = 0; i < lista.size(); ++i)
			{
				while (lista[i].size()>size) lista[i] = lista[i].substr(0, lista[i].size()-1);
				while (lista[i].size()<size) lista[i]+=' ';
				objektumok.push_back( new STATTEXT(TEXT_RAHAGYAS,TEXT_RAHAGYAS+(gout.cascent()+TEXT_RAHAGYAS*4)*(i+1),szin,szin2,lista[i]) );
			}
			if (lista.size()>0)
			{
				kivalasztva=2;
				objektumok[kivalasztva]->setter(cin);
			}
		}

		bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
		void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat.
		void getter(ostream& ki) const;
		void setter(istream& be);
};

bool KIVALASZTO::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
		{
			double ux,uy; // Kamera elmozdulás miatt kellenek.
			ux=x+X0;uy=y+Y0;
			kamera.getKamCoords(ux,uy);
			for (int i = objektumok.size()-1; i >= 2; i--)
			{
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {
					objektumok[kivalasztva]->setter(cin);
					objektumok[i]->setter(cin);
					kivalasztva=i;
					return true;
				}
			}
			
		}
		else if (ev.button==btn_wheelup)
		{
			double ox,oy;
			objektumok[0]->getPosition(ox,oy); if (oy>0) return false;
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				objektumok[i]->getPosition(ox,oy);
				objektumok[i]->setPosition(ox,oy+(gout.cascent()+TEXT_RAHAGYAS*4));
			}
			return true;
		}
		else if (ev.button==btn_wheeldown)
		{
			double ox,oy;
			objektumok[1]->getPosition(ox,oy); 
			if (oy<sy) return false;
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				objektumok[i]->getPosition(ox,oy);
				objektumok[i]->setPosition(ox,oy-(gout.cascent()+TEXT_RAHAGYAS*4));
			}
			return true;
		}
	}
	return false; // Nem fogja el, (pl így el lehet húzni az alatta lévő ablakkal együtt.)
}

void KIVALASZTO::getter(ostream& ki) const 
{
	if (!(kivalasztva<objektumok.size())) return;
	objektumok[kivalasztva]->getter(ki);
}

void KIVALASZTO::setter(istream& be)
{
	string uj;
	be >> uj;

	int van = -1; // Ha van ilyen töröljük, ha nincs hozzáadjuk.

	for (int i = 2; i < objektumok.size(); ++i)
	{	
		stringstream ki;
		objektumok[i]->getter(ki);
		string regi;
		ki >> regi;
		if (regi==uj) {van=i;break;}
	}

	if (van==-1){
		while (uj.size()>size) uj = uj.substr(0, uj.size()-1);
		while (uj.size()<size) uj+=' ';
	
		double ox,oy;
		objektumok[1]->getPosition(ox,oy);
		objektumok.push_back( new STATTEXT(ox,oy,szin2,szin,uj) );
		objektumok[1]->setPosition(ox,oy+(gout.cascent()+TEXT_RAHAGYAS*4));
	
	}else
	{	
		double ox1,oy1,ox2,oy2;
		objektumok[objektumok.size()-1]->getPosition(ox1,oy1); // bezáró elem új poz

		ox2=ox1; oy2=oy1; objektumok[1]->getPosition(ox1,oy1);
		objektumok[1]->setPosition(ox2,oy2);
		for (int i = van; i<=objektumok.size()-1 ; ++i) // visszatolja fentről a lyukba a lista elemeit
		{
			ox2=ox1; oy2=oy1; objektumok[i]->getPosition(ox1,oy1);
			objektumok[i]->setPosition(ox2,oy2);
		} 

		delete objektumok[van];
		objektumok.erase(objektumok.begin()+van); // És törlés rendeltetés szerűen.

		if (kivalasztva==van)
		{
			if (kivalasztva==objektumok.size()) kivalasztva--;
			objektumok[kivalasztva]->setter(cin);
		}else if(kivalasztva>van)
		{
			kivalasztva--;
		}

	}
}

#endif