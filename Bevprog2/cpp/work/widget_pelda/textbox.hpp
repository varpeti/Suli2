#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "graphics.hpp"
#include "widgets.hpp"
#include <string>

using namespace std;
using namespace genv;

class TEXTBOX : public STATTEXT {
public:
	TEXTBOX(int x, int y, int sx, int sy);
	TEXTBOX(int x, int y, int sx, int sy, string str);
	virtual void draw() const;
	virtual void handle(genv::event ev);
};

TEXTBOX::TEXTBOX(int x, int y, int sx, int sy)
	: STATTEXT(x,y,sx,sy,"")
{}

TEXTBOX::TEXTBOX(int x, int y, int sx, int sy, string str)
	: STATTEXT(x,y,sx,sy,str)
{}

void TEXTBOX::draw() const
{
	gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x, _y) << color(255,255,255) << text(str);
}

void TEXTBOX::handle(event ev)
{
	if (ev.type == ev_key) {
		if (ev.keycode>31) str+=ev.keycode;
	}
	cout << str << endl;
}



#endif // TEXTBOX
