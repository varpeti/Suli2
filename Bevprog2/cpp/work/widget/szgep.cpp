#include "env.hpp"
#include "ablak.hpp"
#include "stattext.hpp"
#include "textbox.hpp"
#include "szambox.hpp"
#include "szambeallito.hpp"
#include "kivalaszto.hpp"

class szgep : public ABLAK
{
	int s1,s2,muv; // muv: 0 semmi, 1 +, 2 -, 3 *, 4 /
public:
	szgep() : ABLAK(100,100,500,400,SZIN(200,100,100))
	{
		objektumok.push_back( new STATTEXT(0*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"0") );
		objektumok.push_back( new STATTEXT(1*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"1") );
		objektumok.push_back( new STATTEXT(2*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"2") );
		objektumok.push_back( new STATTEXT(3*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"3") );
		objektumok.push_back( new STATTEXT(4*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"4") );
		objektumok.push_back( new STATTEXT(5*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"5") );
		objektumok.push_back( new STATTEXT(6*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"6") );
		objektumok.push_back( new STATTEXT(7*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"7") );
		objektumok.push_back( new STATTEXT(8*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"8") );
		objektumok.push_back( new STATTEXT(9*20+10,0*20+10,SZIN(0,0,0),SZIN(255,255,255),"9") );
		objektumok.push_back( new STATTEXT(0*20+10,1*20+10,SZIN(0,0,0),SZIN(255,255,255),"+") ); //10
		objektumok.push_back( new STATTEXT(1*20+10,1*20+10,SZIN(0,0,0),SZIN(255,255,255),"-") );
		objektumok.push_back( new STATTEXT(2*20+10,1*20+10,SZIN(0,0,0),SZIN(255,255,255),"*") );
		objektumok.push_back( new STATTEXT(3*20+10,1*20+10,SZIN(0,0,0),SZIN(255,255,255),"/") );
		objektumok.push_back( new STATTEXT(3*20+10,1*20+10,SZIN(0,0,0),SZIN(255,255,255),"=") ); //14
		s1=0;s2=0;muv=0;
	}

	virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera);
	
};

bool szgep::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
		{
			double ux,uy; // Kamera elmozdulás miatt kellenek.
			ux=x+X0;uy=y+Y0;
			kamera.getKamCoords(ux,uy);
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {
					if (i<10) s1=s1*10+i;
					else if (i>=10 and i<=14) {
						if 		(muv==1) {s2=s1+s2;s1=0;}
						else if (muv==2) {s2=s1-s2;s1=0;}
						else if (muv==3) {s2=s1*s2;s1=0;}
						else if (muv==4) {s2=s1/s2;s1=0;}
						else {s2=s1; s1=0;}
						muv=i-9;
						if (muv==5) {s1=s2;s2=0;}
					}
					cout << s1  << " " << s2  << " " << muv << endl;
					return true;
				}
			}
			
		}
	}
	return false; // Nem fogja el, (pl így el lehet húzni az alatta lévő ablakkal együtt.)
}

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.kepek_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	OBJ *sz = new szgep(); env.addObj(sz);

	gin.timer(20);

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		env.UpdateDrawHandle();
	}


	return 0;
}
