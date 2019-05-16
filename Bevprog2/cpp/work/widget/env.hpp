//	Minden objektumban úlyabb objektumok lehetne. És mivel volt gyerekválalási tanácsdónál ezért különbőző típúsú objektumok lehetnek egymásba.
//	Az alobjektumok relatív koordinátával rendelkeznek, a "felettük" lévő bal felső sarka a (0,0) pont.
// Két példa, ahol az OBJ alat bármilyen leszármaztatott osztályt lehet érteni.
//
//		___OBJ[0]___________________ 		___OBJ[1]________________
//		|	___OBJ[0].OBJ[0]_____ 	|		|	___OBJ[1].OBJ[1]_	|
//		|	|					|	|		|	|				|	|
//		|	|OBJ[0].OBJ[0].OBJ_ |	|		|	|_______________|	|
//		|	||________________|	|	|		|	___OBJ[1].OBJ[2]_	|
//		|	|___________________|	|		|	|_______________|	|
//		|___________________________|		|_______________________|
//
// Rajzolsá paraméterei:
//		canvas	- A képeket tartalmazó canvas
//		X0,Y0	- A felette lévő OBJEKTUM (vagy képernyő) bal felső sarka. Azért kell külön ez is mert relatív koordináták vannak.
//		Xb,Yb	- A felette lévő OBJEKTUM a még látható, kirajzolt balfelső sarka. 
//		Xj,Yj	- A felette lévő OBJEKTUM (a még látható, kirajzolt) jobb alsó sarka. Megegyezik az XX,YY pontal az supdate-ben.
// 		kamera 	- A kamera


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

/* OBJ-ektum class */ // ebből örőklődik minden

class OBJ // Az szülő
{
	protected:
		double x,y; //x,y
		double sx,sy; //méret
		vector<OBJ*> objektumok; // Pl ablakban lehetnek widgetek, de akár több ablak is, vagy egy legördülő widgetben több statikus szöveg widget.
		bool mozgathato; // Mozgathatóság

	public:
		OBJ (double x,double y,double sx,double sy,bool mozgathato=true) : x(x), y(y), sx(sx), sy(sy), mozgathato(mozgathato) {lenyomva=false; ex=0; ey=0;};
		~OBJ () {while(objektumok.size()>0){delete objektumok[objektumok.size()-1]; objektumok.pop_back(); }}; // Minden alosztály tartalmát is kiszedi a memóriából.
		virtual void srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera, bool focus) const =0; // sprite, felette, határai b-balfelső j-jobbalsó, kamera
		virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera) {};
		virtual void getter(ostream& ki) const {}; // Adatok kiadására jó.
		virtual void setter(istream& be) {} // Adatok változtatására jó.
		virtual void addObj(OBJ* obj);
		void delObj(OBJ* obj);

		// Azért nem hülyeség a getter és setter mert SEXYBB mint a mezők :D | Egyébként az adatok főleg párosával vannak.
		void setPosition(double x,double y);
		void getPosition(double &x,double &y);
		void setMeret(double sx,double sy);
		void getMeret(double &sx,double &sy);
		bool isMozgathato();

		void ObjKiemel(OBJ *obj);
		bool BenneVan(double px, double py);

	protected:
		bool lenyomva; // A tartalom mozgatáshoz kell.
		double ex,ey;
};

void OBJ::addObj(OBJ *obj)
{
	objektumok.push_back(obj);
}

void OBJ::ObjKiemel(OBJ *obj)
{
	for (int i = 0; i < objektumok.size(); ++i)
		if (objektumok[i]==obj)
		{
			objektumok.push_back(obj);
			objektumok.erase(objektumok.begin()+i);
			return;
		}
}

void ENV::delObj(OBJ *obj)
{	
	int id;
	for (int i = 0; i < objektumok.size(); ++i) // Megekerssük az ID-jét
	{
		if (objektumok[i]==obj) {id=i;break;}
	}
	delete obj;
	objektumok.erase(objektumok.begin()+id);
}

void OBJ::setPosition(double ux,double uy)
{
	x=ux;
	y=uy;
}

void OBJ::getPosition(double &ux,double &uy)
{
	ux=x;
	uy=y;
}

void OBJ::setMeret(double usx,double usy)
{
	sx=usx;
	sy=usy;
}

void OBJ::getMeret(double &usx,double &usy)
{
	usx=sx;
	usy=sy;
}

bool OBJ::isMozgathato()
{
	return mozgathato;
}

bool OBJ::BenneVan(double px, double py)
{
	if (px>=x and px<=x+sx and py>=y and py<=y+sy) return true;
	return false;
};


/* CLASS 	*/

class ENV
{
	public:
		canvas Tkepek;	//az összes OBJ képét ide olvasom be
	
		unsigned int XX;
		unsigned int YY;
	
		// mezők;
		event ev;
		KAMERA kamera;
	
		//konst dest
		ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
		ENV(unsigned int szelesseg, unsigned int magassag);
		~ENV();
	
		// tagfüggvények
		void UpdateDrawHandle();
		bool kepek_beolvas(const char *fname); // BMP-ből olvassa be az összes képet
		void timer(int ido);
	
		void addObj(OBJ* obj);
		void ObjKiemel(OBJ *obj); // Előre hozza az objektumot
		void delObj(OBJ* obj);

	private:
		vector<OBJ*> objektumok; // Az összes obj
};

/* MEGVALÓSÍTÁS */

//konst

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	YY=magassag;
	XX=szelesseg;
	gout.open(XX,YY,teljeskepernyo);
	Tkepek.transparent(true);

}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	YY=magassag;
	XX=szelesseg;
	gout.open(XX,YY);
	Tkepek.transparent(true);
}

ENV::~ENV() //dest
{

}

void ENV::addObj(OBJ *obj)
{
	objektumok.push_back(obj);
}

void ENV::ObjKiemel(OBJ *obj)
{
	for (int i = 0; i < objektumok.size(); ++i)
		if (objektumok[i]==obj)
		{
			objektumok.push_back(obj);
			objektumok.erase(objektumok.begin()+i);
			return;
		}
}

void ENV::delObj(OBJ *obj)
{	
	int id;
	for (int i = 0; i < objektumok.size(); ++i) // Megekerssük az ID-jét
	{
		if (objektumok[i]==obj) {id=i;break;}
	}
	delete obj;
	objektumok.erase(objektumok.begin()+id);
}

void ENV::UpdateDrawHandle()
{
	if (objektumok.size()<1) return;

	static bool lenyomva=false; 
	static double ex=0,ey=0;

	if (ev.type==ev_timer)
	{
		gout << color(0,0,0) << move_to(0,0) << box(XX,YY);

		for (int i = 0; i < objektumok.size();++i) // Saját objektumai
		{
			objektumok[i]->srajzol(Tkepek,0,0,0,0,XX,YY,kamera,i+1==objektumok.size()); // saját mérete a benne lévők korlátja
		}

		gout << refresh;
									    // A legfelső (fókuszban lévő) megkapja az inputokat. És ha mozgott nem tér vissza.
	}else if (objektumok.size()!=0 and !objektumok[objektumok.size()-1]->supdate(ev,0,0,kamera) and ev.type==ev_mouse) 
	{
		if (ev.button==btn_left)
		{
			double uX0=0,uY0=0;
			kamera.getKamCoords(uX0,uY0);
			for (int i = objektumok.size()-1; i >= 0; i--)
				if (objektumok[i]->BenneVan(ev.pos_x-uX0,ev.pos_y-uY0)) 
				{
					objektumok[i]->getPosition(ex,ey);
					ex-=ev.pos_x;
					ey-=ev.pos_y;
					lenyomva=true;
					ENV::ObjKiemel(objektumok[i]);
					break;
				}
		}

		if (-ev.button==btn_left) {lenyomva=false; ex=0; ey=0;}

		if (lenyomva) objektumok[objektumok.size()-1]->setPosition(ev.pos_x+ex,ev.pos_y+ey);
	}
}

void ENV::timer(int ido)
{
	gin.timer(ido);
}

bool ENV::kepek_beolvas(const char *fname) // CSAK azért is BMPből.
{
	FILE* f = fopen(fname, "rb"); if (!f) return false;
	char info[54] = {0}; // 54 byte: az infók
	fread(info, sizeof(char), 54, f); 

	unsigned int width = *(int*)&info[18]; //18. szélesség
	unsigned int height = *(int*)&info[22]; //22. magasság

	unsigned int size = 3 * width * height; // 3 byte pixelenként
	char* data = new char[size]; // lefoglalás
	fread(data, sizeof(char), size, f); // beolvasás egyszerre / csak ha nincsenek színtérinformációk, különben csúszik
	fclose(f);

	Tkepek.open(width,height); // canvas megnyitása
	unsigned int k = 0;
	for (unsigned int i = 0; i < height; i++) //y
	{
		for (unsigned int j = 0; j < width; j++) //x
		{
			unsigned int bb = data[k]; k++; // Igen a mikrofos BBGGRR formátumot használ
			unsigned int gg = data[k]; k++;
			unsigned int rr = data[k]; k++;
			Tkepek << move_to(j,height-i) << color(rr,gg,bb) << dot; // ja és fejjel lefele (MIÉRT???)
		}
	}
	delete data; //Nem használt memória felszabadítása
	return true;
}

#endif