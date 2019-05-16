#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "algorithm"

#define PI 3.141592

using namespace genv;
using namespace std;

const int kx = 1330;
const int ky = 600;
const int kz = round((kx+ky)/2);
const bool teljes = true;
int elemszam = 5; //*3*255


struct Sboxok
{
	double x; //és azért tarton meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	double y;
	double z;
	unsigned char rr,gg,bb;
	double fx; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	double fy; 
	double fz; 

	Sboxok (double ex, double ey, double ez, int szin)
	{
		x = ex;
		y = ey;
		z = ez;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	void supdate(double cx, double cy, double cz);
	void srajzol();

};

double px = PI; double rpx = 0.0;
double py = PI; double rpy = 0.0;
double pz = PI;

std::vector<Sboxok> v;
int szin = 0;
canvas Vp;

void Sboxok::supdate(double cx, double cy, double cz) 
{
	double a = cx-x;
	double b = cy-y;
	double c = cz-z;
	double h = sqrt(a*a+b*b+c*c)/(3); if (h==0) h=1; // normalizásás csak e = 3;
	x+=a/h;
	y+=b/h;
	z+=c/h;

	fx=x; fy=y; fz=z;
	double se;

	//y tengely körüli forgatás (2d-s forgatási mátrixból tippeltem a 3d-st)
	se= fx*cos(px)+fz*sin(px);
	fz= -fx*sin(px)+fz*cos(px);
	fx= se;

	//x tengely körüli forgatás
	se= fy*cos(py)-fz*sin(py);
	fz= fy*sin(py)+fz*cos(py);
	fy= se;

	//z tengely körüli forgatás
	se= fx*cos(pz)-fy*sin(pz);
	fy= fx*sin(pz)+fy*cos(pz);
	fx= se;

}

void Sboxok::srajzol()
{

	//2d leképzés (Leggagyibb ami létezik, de legalább saját)
	int ax = round(fx + fz/2 + kx/2);
	int ay = round(fy + fz/2 + ky/2);

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;

	/*stringstream str;
	str << int(nx) << " " << int(ny) << " " << int(nz);
	string s = str.str();*/

	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
		<< box(-(kz/2+fz)/(kz/2)*10,-(kz/2+fz)/(kz/2)*10); // a Z távolság függvényében változik a méret
}


bool sortZ (const Sboxok &a, const Sboxok &b) { return (a.fz<b.fz); } // Ez felel azért hogy a hátul lévőt elöbb rajzolja ki

void updatedraw()
{
	gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box(kx,ky);


	std::vector<Sboxok> rajZ = v; // új vektor
	std::sort(rajZ.begin(), rajZ.end(), sortZ); // sorba rendezés

	int id = 0;
	for (vector<Sboxok>::iterator i=v.begin(); i!=v.end();)
	{
		int sid=id;
		if (id<v.size()-1) id++; else id=0; 
		i->supdate(v[id].x,v[id].y,v[id].z);
		//i->srajzol();
		rajZ[sid].srajzol(); //az új sorba rendezett vektor alapján rajzolok
		i++;
	}

	gout << stamp(Vp,kx-48,ky-48); // kirajzolom az ikonomat a bal alsó sarokba

	gout << refresh;

}

void BMP(const char *fname,canvas &C); // BMP-ből beolvasás

int main()
{
	srand (time(NULL));
	gout.open(kx,ky,teljes);

	BMP("Vp.bmp",Vp);

	//gout.showmouse(false); 
	for (int i = 0; i < (3*255*elemszam); ++i)
	{
		Sboxok b(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2,szin);
		szin++; if (szin>3*255) szin=0;
		v.push_back(b);
	}

	gin.timer(20);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			updatedraw();

			py+=rpy;
			px+=rpx;
		}
		else if (ev.type==ev_key)
		{
			double mertek = 0.03;
			if (ev.keycode==key_up 		or ev.keycode=='w') rpy=-mertek;
			if (ev.keycode==key_down 	or ev.keycode=='s') rpy=mertek;
			if (ev.keycode==key_right 	or ev.keycode=='d') rpx=mertek;
			if (ev.keycode==key_left 	or ev.keycode=='a') rpx=-mertek;

			if (-ev.keycode==key_up 	or -ev.keycode=='w') rpy=0;
			if (-ev.keycode==key_down 	or -ev.keycode=='s') rpy=0;
			if (-ev.keycode==key_right 	or -ev.keycode=='d') rpx=0;
			if (-ev.keycode==key_left 	or -ev.keycode=='a') rpx=0;
		}
		else if (ev.type==ev_mouse)
		{
			if (ev.button==btn_right) for(Sboxok &i:v) if (rand()%30==3) {i.x=rand()%kx-kx/2;i.y=rand()%ky-ky/2;i.z=rand()%kz-kz/2;} //egy pár random pozícióba
			if (ev.button==btn_left) {v[0].x=rand()%kx-kx/2;v[0].y=rand()%ky-ky/2;v[0].z=rand()%kz-kz/2;} // az első random pozícióba
		}
	}
	return 0;
}

void BMP(const char *fname,canvas &C) // CSAK azért is BMPből.
{

	FILE* f = fopen(fname, "rb"); if (!f) return;
	unsigned char info[54] = {0}; // 54 byte: az infók
	fread(info, sizeof(unsigned char), 54, f); 

	unsigned int width = *(int*)&info[18]; //18. szélesség
	unsigned int height = *(int*)&info[22]; //22. magasság

	unsigned int size = 3 * width * height; // 3 byte pixelenként
	unsigned char* data = new unsigned char[size]; // lefoglalás
	fread(data, sizeof(unsigned char), size, f); // beolvasás egyszerre / csak ha nincsenek színtérinformációk, különben csúszik
	fclose(f);

	C.open(width,height); // canvas megnyitása
	unsigned int k = 0;
	for (unsigned int i = 0; i < height; i++) //y
	{
		for (unsigned int j = 0; j < width; j++) //x
		{
			unsigned int bb = data[k]; k++; // Igen a mikrofos BBGGRR formátumot használ
			unsigned int gg = data[k]; k++;
			unsigned int rr = data[k]; k++;
			C << move_to(j,height-i) << color(rr,gg,bb) << dot; // ja és fejjel lefele (MIÉRT???)
		}
	}
	delete data; //Nem használt memória felszabadítása
}