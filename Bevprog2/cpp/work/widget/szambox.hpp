#ifndef _SZAMBOX_	//ujabb definíció és fordítási hiba elkerülésére
#define _SZAMBOX_

#include "textbox.hpp"
#include <iomanip>

class SZAMBOX : public TEXTBOX
{
	protected:

		double A; // Határértékei
		double B;
		double szam;
		string szoveg2;

	public:

		SZAMBOX(double x, double y, double A, double B, SZIN szin, SZIN szin2, double bszam=0, unsigned int size=8)
			: TEXTBOX(x,y,size,szin,szin2,"0"), A(A), B(B), szam(bszam>A ? bszam<B ? bszam : B : A)
		{
			sx=gout.twidth("0")*size+TEXT_RAHAGYAS;
			ostringstream strs; strs << setprecision(size) << szam; szoveg2 = strs.str();
			szoveg=szoveg2;
			while (szoveg.size()>size) szoveg = szoveg.substr(1, szoveg.size());
		}
	
		virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera);
		virtual void getter(ostream& ki) const;
};

bool SZAMBOX::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_key)
	{
		if ( (ev.keycode>=48 and ev.keycode<=57) or ev.keycode==43 or ev.keycode==45 or ev.keycode==46 or ev.keycode==101) szoveg2+=ev.keycode; // 0123456789+-.e
		else if (ev.keycode==key_backspace) szoveg2 = szoveg2.substr(0, szoveg2.size()-1); // Törlés
		else if (ev.keycode==key_up  ) {if (szam+1<=B) szam=szam+1; ev.keycode=key_enter;} // Növelés
		else if (ev.keycode==key_down) {if (szam-1>=A) szam=szam-1; ev.keycode=key_enter;} // Csökkentés
		else if (ev.keycode==key_pgup) {if (szam+10<=B) szam=szam+10; ev.keycode=key_enter;} // Növelés
		else if (ev.keycode==key_pgdn) {if (szam-10>=A) szam=szam-10; ev.keycode=key_enter;} // Csökkentés
		else if (ev.keycode==key_home) {szam=B; ev.keycode=key_enter;} // MAX
		else if (ev.keycode==key_end ) {szam=A; ev.keycode=key_enter;} // MIN

		if (ev.keycode==key_enter) {ostringstream strs; strs << setprecision(size) << szam; szoveg2 = strs.str();} //Enter után az értelmezhető számot kiírja.

		szam = atof(szoveg2.c_str()); // Ha ki tudja írni rendesen
		szam = szam>A ? szam<B ? szam : B : A; // Határértékek között tartás

		szoveg=szoveg2;
		while (szoveg.size()>size) szoveg = szoveg.substr(1, szoveg.size()); // Nincs több karakter hely, az elejéről "töröl" (csak a kiírást)
		
		return true; // Elfogja a karaktereket.
	}
	return false; // Nem fogja el, (pl így el lehet húzni az alatta lévő ablakkal együtt.)
}

void SZAMBOX::getter(ostream& ki) const 
{
	ki << setprecision(size) << szam;
};


#endif