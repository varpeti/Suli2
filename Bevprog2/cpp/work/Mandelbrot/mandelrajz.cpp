#include "komplex.hpp"
#include "graphics.hpp"
#include <iostream>
#include <cmath>
using namespace genv;

double lex=0,ley=0;


void mandelrajz(int XX, int YY, int MAX, double zoom,double ex,double ey) {

	lex+=(XX/2-ex)*(zoom/double(XX)); // Az előző nagyítás alapján kiszámolja hova hogyan tolja el.
	ley+=(YY/2-ey)*(zoom/double(YY));

	for (int x=0;x<XX;x++) {
		double cr = (zoom/double(XX))*x - zoom/2 -lex;
		for (int y=0;y<YY;y++) {
			double ci = (zoom/double(YY))*y - zoom/2 -ley;
			komplex c(cr, ci);
			komplex z(0,0);
			int t = 0;
			while (z.re()*z.re()+z.im()*z.im() < 1/zoom*16 && t < MAX) {
				z = z*z+c;
				++t;
			}
			t*=(255*3)/MAX; // Ez biztosítja hogy 0-tól 3*255-ig menjen a t;
			double rr,gg,bb;
			if (t<=255) 				{rr=000;				gg=(t-0*255); 		bb=000;} 			else
			if (t>255 and t<=2*255) 	{rr=(t-1*255);			gg=255-(t-1*255); 	bb=000;} 		else
			if (t>2*255) 				{rr=255-(t-2*255);		gg=000; 			bb=000;}
			gout << move_to(x,y) << color(rr,gg,bb) << dot;
		}
		//gout << refresh; // Ez csak azért van hogy lássam betöltődni
	}
	gout << refresh;
}
