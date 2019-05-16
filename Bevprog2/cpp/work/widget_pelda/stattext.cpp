#include "stattext.hpp"
using namespace genv;
using namespace std;

STATTEXT::STATTEXT(int x, int y, string str)
	: Widget(x,y,gout.twidth(str),gout.cascent()), str(str)
{}

STATTEXT::STATTEXT(int x, int y, int sx, int sy, string str)
	: Widget(x,y,sx,sy), str(str)
{}

void STATTEXT::draw() const
{
	gout << move_to(_x, _y) << color(255,255,255) << text(str);
}
