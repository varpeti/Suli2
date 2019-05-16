#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "time.h"
#include "math.h"
#include "iostream"

using namespace genv;
using namespace std;

const int XX = 1330;
const int YY = 600;
const bool teljes = false;

const double maximumsebesseg = 10;

struct Skoordinatak
{
	double x;
	double y;

	Skoordinatak (double ux, double uy) 
	{
		x=ux;
		y=uy;
	};

	Skoordinatak () 
	{};

};

void kor(Skoordinatak pozicio, double sugar)
{
	for (int y = -sugar; y <=sugar; ++y)
	{
		for (int x = -sugar; x <=sugar; ++x)
		{
			if (x*x+y*y-sugar*sugar<1) gout << move_to(x+pozicio.x,y+pozicio.y) << dot;
		}
	}
}

struct Sgolyo
{
	private:
	double sugar;
	Skoordinatak pozicio;
	Skoordinatak sebesseg;
	unsigned char R,G,B;

	public:
	Sgolyo (double usugar, Skoordinatak upozicio, Skoordinatak usebesseg) 
	{
		sugar = usugar;
		pozicio = upozicio;
		sebesseg = usebesseg;
		R = rand()%255;
		G = rand()%255;
		B = rand()%255;
	};

	void rajzol()
	{
		gout << color(R,G,B);
		kor(pozicio,sugar);
	}

	void update(vector<Sgolyo> &labdak, double surlodas)
	{
		for (int i = 0; i < labdak.size(); i++) { // Megvizsgálom mindegyikkel, hogy ütközött-e
	 		double dx = labdak[i].pozicio.x - pozicio.x; // Vektort képzek
			double dy = labdak[i].pozicio.y - pozicio.y;
			double distance = sqrt(dx*dx + dy*dy); // távolság
			double minDist = labdak[i].sugar + sugar; // Legkisebb távolság hogy még nem ütközik
	  		if (distance < minDist) { // ütközött-e
				double angle = atan2(dy, dx); // ütközés szöge

				double targetX = pozicio.x + cos(angle) * minDist; // sebesség vektor számolás (előkészület)
				double targetY = pozicio.y + sin(angle) * minDist;

				double ax = (targetX - labdak[i].pozicio.x) * 0.9; // sebesség vektor számolás (befejezés)
				double ay = (targetY - labdak[i].pozicio.y) * 0.9; // A 0.9es szorzó azért van hogy szétjöjjenek ha egyberakjuk őket. (Ugyanakkor rugalmatlanabb lesz az ütközés) 

				sebesseg.x -= ax; // Sebességvektorok megváltozatása
				sebesseg.y -= ay;
				labdak[i].sebesseg.x += ax;
				labdak[i].sebesseg.y += ay;
			}
		}

		if (sebesseg.x>maximumsebesseg) sebesseg.x=maximumsebesseg; else if (sebesseg.x<-maximumsebesseg) sebesseg.x=-maximumsebesseg; // Ha túl gyorsak lennének (ami csak akkor lehet ha egyberakjuk őket)
        if (sebesseg.y>maximumsebesseg) sebesseg.y=maximumsebesseg; else if (sebesseg.y<-maximumsebesseg) sebesseg.y=-maximumsebesseg; // Maximum sebességre állítjuk őket

		pozicio.x+=sebesseg.x; // Mozgatás
		pozicio.y+=sebesseg.y;

		if (pozicio.x-sugar<0) { // Fallakkal való ütközés
			sebesseg.x=-sebesseg.x;
			pozicio.x=0+sugar;
		}
		if (pozicio.x+sugar>XX){
			sebesseg.x=-sebesseg.x;
			pozicio.x=XX-sugar;
		}
		if (pozicio.y-sugar<0) {
			sebesseg.y=-sebesseg.y;
			pozicio.y=0+sugar;
		}
		if (pozicio.y+sugar>YY){
			sebesseg.y=-sebesseg.y;
			pozicio.y=YY-sugar;
		}

		sebesseg.x/=surlodas;
		sebesseg.y/=surlodas;
		cout << surlodas << "	" << int(sebesseg.x*100)/100.0 << "	" << int(sebesseg.y*100)/100.0 << endl;

	}
};


int main()
{
	srand (time(NULL));

	gout.open(XX,YY,teljes);

	gin.timer(20);
	vector<Sgolyo> labdak;

	double surlodas = 1;

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
			for (int i = 0; i < labdak.size(); ++i)
			{
				labdak[i].update(labdak, surlodas);
				labdak[i].rajzol();
			}
			gout << refresh;
		}
		else if (ev.type==ev_mouse)
		{
			if (ev.button==btn_left) {
				Sgolyo labda(rand()%20+3,Skoordinatak(ev.pos_x,ev.pos_y),Skoordinatak((rand()%int(maximumsebesseg*200)-maximumsebesseg*100)/100.0,(rand()%int(maximumsebesseg*200)-maximumsebesseg*100)/100.0));
				// rand()%int(maximumsebesseg*200)-maximumsebesseg*100)/100.0) -nek az értékei ha maximumsebesseg=3: -3.00-tól +3.00-ig
				labdak.push_back(labda);
			}
			else if (ev.button==btn_wheelup) surlodas+=0.001;
			else if (ev.button==btn_wheeldown) surlodas-=0.001;
			if (surlodas<1) surlodas=1;
		}
		else if (ev.type==ev_key)
		{
			
		}
	}
	return 0;
}