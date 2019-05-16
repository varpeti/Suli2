#include "szambeallito.hpp"
#include "kivalaszto.hpp"

using namespace genv;

int main()
{
	srand(time(0));
	ENV env (1300,600,false);
	if(!env.kepek_beolvas("sp.bmp")) gout << text("Nem talalhato a kep!");
	
	OBJ *ablak = new ABLAK(300,100,500,400,0,0); env.addObj(ablak);

	OBJ *szam = new SZAMBEALLITO(25,30,-100,100,SZIN(200,150,100),SZIN(0,0,0),1.234567e-9,12); ablak->addObj(szam);
	OBJ *szam2 = new SZAMBEALLITO(10,110,-3e+09,900,500,1,500,47,SZIN(0,0,0),SZIN(0,255,0)); env.addObj(szam2);
		
	vector<string> lista; lista.push_back("almaspite");lista.push_back("barack");lista.push_back("citrom");lista.push_back("dinnye");lista.push_back("1");lista.push_back("26435");lista.push_back("szilva");
	OBJ *leg = new KIVALASZTO(240,110,SZIN(0,0,0),SZIN(255,255,255),lista); ablak->addObj(leg);

	vector<string> lista2; lista2.push_back("kalap");lista2.push_back("keres");lista2.push_back("koma");lista2.push_back("kukoricapehely");lista2.push_back("ki");lista2.push_back("t");lista2.push_back("tt");lista2.push_back("ttt");
	OBJ *leg2 = new KIVALASZTO(10,220,SZIN(100,75,50),SZIN(200,200,0),lista2,5,14); env.addObj(leg2);

	OBJ *ablakt = new ABLAK(10,550,1500,165,SZIN(100,50,100)); env.addObj(ablakt);

	OBJ *t = new STATTEXT(10,5,SZIN(100,50,100),SZIN(0,0,0),"Informaciokert huzd fel ezt az ablakot."); ablakt->addObj(t);

	OBJ *tszam = new STATTEXT(10,50,SZIN(100,50,100),SZIN(0,0,0),"Home End (max/min), PgUp PgDn (+-10), Fel Le (+-1), Enter (bevitel vege) gombokat kezelik a szambeallitok. Hasznalhato karaktrek: 0123456789.-+e"); ablakt->addObj(tszam);

	OBJ *tleg = new STATTEXT(10,80,SZIN(100,50,100),SZIN(0,0,0),"Az 'F1'-el tudsz uj elemet hozzaadni, a fekete-feher listahoz."); ablakt->addObj(tleg);
	OBJ *tleg2 = new STATTEXT(10,110,SZIN(100,50,100),SZIN(0,0,0),"Kijeloles utan gorgovel lehet gorgetni a listakat."); ablakt->addObj(tleg2);

	OBJ *t2 = new STATTEXT(10,140,SZIN(100,50,100),SZIN(0,0,0),"Az 'F2'-vel kimentheted a beallitott ertekeke a \"ki.txt\" fileba."); ablakt->addObj(t2);

	gin.timer(20);

	bool lenyomva = false;
	double kx=0,ky=0;
	//env.kamera.rset(0,150);

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		
		if (env.ev.type==ev_timer){
			//env.kamera.rset(1,1);
		} 
		else if (env.ev.type==ev_key)
		{
			if (env.ev.keycode==key_f1) {
				stringstream str ("  alma");
				str << rand()%90+10;
				leg->setter(str);
			}
			else if (env.ev.keycode==key_f2)
			{
				ofstream ki ("ki.txt");
				szam->getter(ki); ki << endl;
				szam2->getter(ki); ki << endl;
				leg->getter(ki); ki << endl;
				leg2->getter(ki); ki << endl;
				ki.close();
			}
		}

		env.UpdateDrawHandle();
		
	}

	return 0;
}
