#include "../graphics.hpp"

using namespace genv;

int main()
{
	gout.open(400,400);

	gout << color(000,000,255)
		<< move_to(1,1) 
		<< box_to(399,399);


	gout << color(255,255,255)
		<< move_to(200,100)
		<< line_to(150,300)
		<< line_to(250,300)
		<< line_to(200,100);

	
	gout << refresh;
	event ev;
	while(gin >> ev) {
		if (ev.button==btn_left) {
			gout << line_to(ev.pos_x,ev.pos_y);
			//gout << move_to(ev.pos_x,ev.pos_y) << dot;
		}

		gout << refresh;
	}
	return 0;
}
