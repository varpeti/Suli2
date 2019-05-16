#include "graphics.hpp"
#include "sstream"

using namespace genv;
using namespace std;

int main()
{
	gout.open(400,400);

	event ev;
	while(gin >> ev) {
		gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box_to(399,399);
		
		gout << color(255,255,255) 
			<< move_to(200,200) 
			<< line_to(ev.pos_x,ev.pos_y);

		stringstream str;
		str << ev.pos_x << " : " << ev.pos_y;
		string s = str.str();
		gout << move_to(20,20) 
			<< text(s);

		gout << move_to(22,22) << line(gout.twidth(s),0);



		gout << refresh;
	}
	return 0;
}
