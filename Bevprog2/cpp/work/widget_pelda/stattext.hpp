#ifndef STATTEXT_H
#define STATTEXT_H

#include "graphics.hpp"
#include "widgets.hpp"
#include <string>

using namespace std;

class STATTEXT : public Widget {
protected:
	string str;
public:
	STATTEXT(int x, int y, string text);
	STATTEXT(int x, int y, int sx, int sy, string text);
	virtual void draw() const;
};


#endif // STATTEXT
