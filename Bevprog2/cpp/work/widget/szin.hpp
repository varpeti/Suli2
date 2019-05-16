#ifndef _SZIN_	//ujabb definíció és fordítási hiba elkerülésére
#define _SZIN_

struct SZIN
{
	char rr,gg,bb;

	SZIN(char rr,char gg,char bb) : rr(rr), gg(gg), bb(bb) {};

	SZIN() : rr(0), gg(0), bb(0) {};
};

#endif