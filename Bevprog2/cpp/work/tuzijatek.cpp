//CODEINGAME
#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"

using namespace genv;
using namespace std;

const int kx = 1330;
const int ky = 600;

struct Sboxok
{
	int x;
	int y;
	int vx;
	int vy;
	unsigned char rr,gg,bb;
	int elet;

	Sboxok (int ex, int ey, int szin)
	{
		x = ex;
		y = ey;
		vx=rand() % 10 -5;
		vy=-(rand() % 10 +5);
		elet = 100;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	void supdate();
	void srajzol();

};

void Sboxok::supdate() 
{
	x+=vx;
	y+=vy;
	if (x>=kx or x<0) {vx=-vx; x+=vx;}
	if (y>=ky or y<0) {vy=-floor(vy/2); y+=vy;}
	vy++;
	elet--;
}

void Sboxok::srajzol()
{
	if (x>=kx or x<0) return;
	if (y>=ky or y<0) return;
	gout << color(rr,gg,bb)
		<< move_to(x,y)
		<< box(10,10);
}

std::vector<Sboxok> v;
int szin = 0;

void updatedraw()
{

	for (vector<Sboxok>::iterator i=v.begin(); i!=v.end();)
	{
		i->supdate();
		i->srajzol();
		if(i->elet<=0) i = v.erase(i);
		else ++i;
	}
}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,true);

	gout.showmouse(false); 

	gin.timer(20);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box_to(1329,599);

			updatedraw();

			gout << refresh;
		}
		else if (ev.type==ev_mouse)
		{
			Sboxok b(ev.pos_x,ev.pos_y,szin);
			szin++; if (szin>3*255) szin=0;
			v.push_back(b);
		}
	}
	return 0;
}
