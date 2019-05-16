#include "graphics.hpp"

using namespace genv;

int main()
{
	gout.open(400,400);

	for (int i = 0; i < 10; ++i)
	{
		gout << color(155+i*10,255-i*10,000) 
			<< move_to(200,100+i*10)
			<< line_to(200-i*10,200);

		gout << color(155+i*10,255-i*10,000) 
			<< move_to(200,300-i*10)
			<< line_to(200+i*10,200);

		gout << color(155-i*10,155+i*10,000) 
			<< move_to(100+i*10,200)
			<< line_to(200,200+i*10);

		gout << color(155-i*10,155+i*10,000) 
			<< move_to(300-i*10,200)
			<< line_to(200,200-i*10);


	}

	
	gout << refresh;
	event ev;
	while(gin >> ev) {
	}
	return 0;
}
