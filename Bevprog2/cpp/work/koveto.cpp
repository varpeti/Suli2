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
const bool teljes = false;

int ex = 0;
int ey = 0;

int ox = 0;
int oy = 0;

struct Sboxok
{
	int x;
	int y;
	unsigned char rr,gg,bb;

	Sboxok (int ex, int ey, int szin)
	{
		x = ex;
		y = ey;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	void supdate(int cx, int cy);
	void srajzol();

};

void Sboxok::supdate(int cx, int cy) 
{
	int a = cx-x;
	int b = cy-y;
	int h = floor( (abs(a)+abs(b))/(rand()%10+3) ); if (h==0) h=1;
	x+=ceil(a/h)+ex;
	y+=ceil(b/h)+ey;

	if ((x>=kx or x<0) or (y>=ky or y<0) ) {x=rand()%(kx-100)+50; y=rand()%(ky-100)+50;}

}

void Sboxok::srajzol()
{
	//if (x>=kx or x<0) return;
	//if (y>=ky or y<0) return;
	gout << color(rr,gg,bb)
		<< move_to(x,y)
		<< box(10,10);
}

std::vector<Sboxok> v;
int szin = 0;

void updatedraw()
{

	int id = 0;
	for (vector<Sboxok>::iterator i=v.begin(); i!=v.end();)
	{
		if (id<v.size()-1) id++; else id=0; 
		i->supdate(v[id].x,v[id].y);
		i->srajzol();
		i++;
	}
	v[0].x+=ox;
	v[0].y+=oy;
}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,teljes);

	gout.showmouse(false); 

	for (int i = 0; i < (3*255*2); ++i)
	{
		Sboxok b(rand()%(kx-100)+50,rand()%(ky-100)+50,szin);
		szin++; if (szin>3*255) szin=0;
		v.push_back(b);
	}

	gin.timer(20);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box(kx,ky);

			updatedraw();

			gout << refresh;
		}
		if (ev.type==ev_key)
		{
			if (ev.keycode==key_up 		) ey--;
			if (ev.keycode==key_down 	) ey++;
			if (ev.keycode==key_right 	) ex++;
			if (ev.keycode==key_left 	) ex--;

			if (ev.keycode=='w') oy--;			
			if (ev.keycode=='s') oy++;
			if (ev.keycode=='d') ox++;
			if (ev.keycode=='a') ox--;

		}
		
	}
	return 0;
}
