#include "graphics.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "mandelrajz.hpp"
#include "komplex.hpp"

using namespace genv;
using namespace std;

const int XX=800;
const int YY=600;


int MAX = 255;

double nagyitas = 4;

int main()
{
	gout.open(XX,YY);

	mandelrajz(XX,YY, MAX, nagyitas, XX/2, YY/2); gout << refresh;

	event ev;
	while(gin >> ev && ev.keycode != key_escape) {
		if (ev.type==ev_mouse and ev.button==btn_left)
		{
			nagyitas/=2;
			mandelrajz(XX,YY, MAX,nagyitas,ev.pos_x,ev.pos_y);
			cout << double(ev.pos_x)/XX << " " << double(ev.pos_y)/YY << endl;
			
		}

	}

	return 0;
}

