#include "graphics.hpp"
#include "string"
#include "vector"
#include "time.h"
#include "math.h"
#include "iostream"

using namespace genv;
using namespace std;

// Környezeti konstansok
const int kx = 1330;
const int ky = 700;
const bool teljes = false;
const int nagyszam = kx+ky;
const int megevesitav = 10;

// Játék konstansok
const int egyedf = 10;
const int egyedb = 50;

const double baranyseb = 3.4; // Maximum sebesség
const double baranyteh = 60; // Tehetetlenség
const double farkasseb = 3.8;
const double farkasteh = 75; //Ezekkela konstansokkal játszva lehet kapni érdekes "játékokat:" pl cápák vs halak, ufók vs tehenek stb

//Debug
bool DEBUG = false;

class Sboxok
{
	public:

	double x,y;
	double vx,vy;
	double sx,sy; // Csak hogy szépen menjen ki a képernyőröl (méret)
	double tehetetlenseg;
	double maxseb;
	int szam;
	unsigned char rr,gg,bb;

	Sboxok (double x, double y, double maxseb, double tehetetlenseg, int szin)
		: x(x), y(y), sx(10), sy(10), vx(0), vy(0), maxseb(maxseb), tehetetlenseg(tehetetlenseg), szam(0)
	{
		if (szin<=255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<=2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	};

	void supdate(double mx, double my, bool fele);
	void srajzol();

	virtual bool farkase() = 0;
};

struct Sfarkas : Sboxok
{
	Sfarkas(double x, double y, int szin) : Sboxok(x,y,farkasseb,farkasteh,szin) {};

	bool farkase() {return true;};
};

struct Sbarany : Sboxok
{
	Sbarany(double x, double y, int szin) : Sboxok(x,y,baranyseb,baranyteh,szin) {};

	bool farkase() {return false;};
};

void Sboxok::supdate(double mx, double my, bool fele) 
{	
	if (mx!=-1)
	{	
		double a = mx-x;
		double b = my-y;
		double h = ( sqrt(a*a+b*b) )/(rand()%10+3)*tehetetlenseg; if (h==0) h=1;
		if (fele) {vx+=a/h;vy+=b/h;}
		else {vx-=a/h;vy-=b/h;}		

		if (vx>maxseb) vx=maxseb; else if (vx<-maxseb) vx=-maxseb;
		if (vy>maxseb) vy=maxseb; else if (vy<-maxseb) vy=-maxseb;
	}

	x+=vx;
	y+=vy;

	if (x+sx<0) x=kx-1; if (x>kx) x=1;
	if (y+sy<0) y=ky-1; if (y>ky) y=1;

	if (DEBUG and mx!=-1)
	{
		if (!fele) gout << color(0,255,0); else gout << color(255,0,0);
		gout << move_to(x,y) << line_to(mx,my);
	}
}

void Sboxok::srajzol()
{
	// Hogy ki tudjon lógi a képernyőről
	double ux,uy,usx,usy,ukx,uky;
	ux=x;uy=y;usx=sx;usy=sy;
	if (ux+usx<0 or ux>kx or uy+usy<0 or uy>ky) return; // Ha teljesen kint van
	if (ux+usx>kx) {usx=kx-ux;}
	if (ux<0) {usx+=ux; ux=0;}
	if (uy+usy>ky) {usy=ky-uy;}
	if (uy<0) {usy+=uy; uy=0;}
	gout << color(rr,gg,bb) << move_to(ux,uy) << text(to_string(szam)); // Csak a számot írjuk ki
}

double tavolsag(Sboxok *barany,Sboxok *farkas)
{	

	double tav = sqrt( (farkas->x-barany->x)*(farkas->x-barany->x)+(farkas->y-barany->y)*(farkas->y-barany->y) );
	if (tav>ky/2) tav=nagyszam;
	return tav;
}

void ujegyedek(vector<Sboxok*> &egyedek,int f,int b)
{
	for (int i = 0; i < f; ++i) //Létrehzom a bárányokat és a farkasokat
	{
		Sboxok *farkas = new Sfarkas(rand()%kx,rand()%ky,rand()%50); // x, y, szín (vörös)

		egyedek.push_back(farkas);
	}

	for (int i = 0; i < b; ++i)
	{
		Sboxok *barany = new Sbarany(rand()%kx,rand()%ky,rand()%50+255); //(zöld)

		egyedek.push_back(barany);
	}
}

void updatedraw(vector<Sboxok*> &egyedek)
{

	for (int i = 0; i < egyedek.size();)
	{	
		double mintav = nagyszam; //Ennél távolabb nem lehet :D
		int minId = -1; //azért int és nem mutató mert így könnyebb törölni
		for (int j = 0; j < egyedek.size(); ++j)
			if (egyedek[i]->farkase()!=egyedek[j]->farkase()) // Fajtársakkal nem nézünk távolságot.
			{
				double tav = tavolsag(egyedek[i],egyedek[j]); // Lényegtelen melyik a farkas
				if (tav<mintav) {mintav=tav; minId=j;} //Minimum kiválasztás
			}

		double mx=-1,my=-1; // változatlanul menjen tovább előre.

		if (minId!=-1)
		{
			if (mintav<megevesitav and !egyedek[i]->farkase()) //Barany aki elég közel került egy farkashoz
			{
				// Szabályos cserés törlés memória felszabadítással
				delete egyedek[i];
				egyedek[i] = egyedek[egyedek.size()-1];
				egyedek.pop_back();

				egyedek[minId]->szam++; // Farkas frag növelés

				if (egyedek.size()-1==egyedf) ujegyedek(egyedek,0,egyedb);

				continue; // Mivel nem nő a ciklusváltozó a kicserélt egyed se lesz kihagyva
			}
			mx=egyedek[minId]->x;
			my=egyedek[minId]->y;
		}


		egyedek[i]->supdate(mx,my,egyedek[i]->farkase());
		egyedek[i]->srajzol();
		i++; // csak akkor növelem ha végére ért.
	}
}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,teljes);

	//gout.showmouse(false);

	vector<Sboxok*> egyedek;
	ujegyedek(egyedek,egyedf,egyedb);

	gin.timer(20);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box(kx,ky);

			updatedraw(egyedek);

			gout << refresh;
		}else if (ev.type==ev_key)
		{
			DEBUG=!DEBUG;
		}
	}

	while(egyedek.size()>0) // takarítás
	{
		delete egyedek[egyedek.size()-1];
		egyedek.pop_back();
	}
	
	return 0;
}