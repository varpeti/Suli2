#include <iostream>
#include <vector>
#include "time.h"
#include "math.h"
using namespace std;

const int kezdeti_toronymagassag = 20;
const int kezdeti_falmagassag = 10;
const int kezdeti_penz = 30;
const int kezdeti_mana = 30;

class Jatekos;
class Vilag;

class Kartya {
		int koltseg_penz, koltseg_mana;
	public:
		Kartya(int p, int m) : koltseg_penz(p), koltseg_mana(m) {}
		virtual string nev()=0;
		virtual void kijatszik(Jatekos *kire, Jatekos *ki)=0;
};

class Jatekos {
		Vilag * vilag;
		int falmagassag, toronymagassag, mana, penz;
		vector<Kartya *> kartyak;
	public:
		Jatekos(Vilag *v) : vilag(v),
			falmagassag(kezdeti_falmagassag),
			toronymagassag(kezdeti_toronymagassag),
			mana(kezdeti_mana),
			penz(kezdeti_penz)
		{}
		void random_lep();
		void serul(int utes) {
			falmagassag -= utes;
			if (falmagassag<0) {
					toronymagassag += falmagassag;
					falmagassag = 0;
			}
		}
		void HPup(int heal) {
			if (falmagassag+heal<=kezdeti_falmagassag)
				falmagassag += heal;
			else
				falmagassag=kezdeti_falmagassag;
		}
		void torony_ut(int utes) {
			toronymagassag -= utes;
		}
		bool vesztett() {
			return toronymagassag <= 0;
		}
		void kap(Kartya *k) {
			kartyak.push_back(k);
		}
		bool status(ostream &out) {
			out <<"torony: " << toronymagassag << " fal: " << falmagassag << " penz:" << penz << " mana:" << mana << endl;
			for (Kartya * k : kartyak ) {
					out << k->nev() << " ";
			}
			out << endl;
			return toronymagassag>0;
		}
		int get_falmagassag() {return falmagassag;}
};

class Vilag {
		Jatekos *jatekos_a, *jatekos_b;
public:
		Vilag() {
			jatekos_a = new Jatekos(this);
			jatekos_b = new Jatekos(this);
		}
		void random_oszt();
		bool report() {
			bool vege = true;
			cout << "A: " << endl;
			if (!jatekos_a->status(cout)) vege=false;
			cout << "B: " << endl;
			if (!jatekos_b->status(cout)) vege=false;
			cout << " ------ " << endl;
			return vege;
		}
		void a_random_lep() {
			jatekos_a->random_lep();
		}
		void b_random_lep() {
			jatekos_b->random_lep();
		}
		void kijatszik(Jatekos * ki, Kartya * mit) {
			Jatekos * kire;
			if (ki == jatekos_a) {
					kire = jatekos_b;
					cout << "A kijatszik " << mit->nev() << endl;
			} else {
					kire = jatekos_a;
					cout << "B kijatszik " << mit->nev() << endl;
			}

			mit->kijatszik(kire, ki);
		}
};

class UtoKartya : public Kartya {
		int utesero;
	public:
		UtoKartya(int p, int m, int utes) : Kartya(p,m), utesero(utes)
		{
		}
		virtual void kijatszik(Jatekos * kire, Jatekos * ki) {
				kire->serul(utesero);
		}
};

class HealKartya : public Kartya {
		int heal;
	public:
		HealKartya(int p, int m, int heal) : Kartya(p,m), heal(heal)
		{}
		virtual void kijatszik(Jatekos * kire, Jatekos * ki) {
				ki->HPup(heal);
		}
};

// Pap egy healler kártya

class Pap : public HealKartya {
	public:
		Pap() : HealKartya(10,5,6) {}
		virtual string nev() {
			return "Pap";
		}
};

// Az Ogre egy egyszerű ütőkártyára példa

class Ogre : public UtoKartya {
	public:
		Ogre() : UtoKartya(20,0,12) {}
		virtual string nev() {
				return "Ogre";
		}
};

// az Íjászok át tudnak lőni a falon, ha a saját faluk magasabb, ilyenor többet sebeznek

class Ijasz : public Kartya {
public:
		Ijasz() : Kartya(7,1) {}
		virtual string nev() {
				return "Ijasz";
		}
		virtual void kijatszik(Jatekos * kire, Jatekos * ki) {
				if (ki->get_falmagassag() > kire->get_falmagassag()) {
						kire->torony_ut(5);
				} else {
						kire->serul(2);
				}
		}
};

void Vilag::random_oszt() {
		for (int i=0;i<5;i++) {
			for(Jatekos *ki : {jatekos_a, jatekos_b} )
			{
				Kartya * uj;
				int melyik = rand() % 3; //hányféle fajta kártya van
				switch (melyik) {
						case 0 : uj = new Ogre; break;
						case 1 : uj = new Ijasz; break;	//figyelj, hogy mindig legyen break!
						case 2 : uj = new Pap; break;
				}
				ki->kap(uj);
			}
		}
}

void Jatekos::random_lep() {
		Kartya * k = kartyak.at(rand()%(kartyak.size()-1));
		vilag->kijatszik(this, k);
}


// Tesztelés a main()-ben. Később rendes játékot lehet belőle csinálni, most csak mindent kipróbálunk ami eszünkbe jut.

int main()
{
	srand(time(0));
	Vilag v;
	v.random_oszt();

	bool kikore = false;
	while (v.report())
	{
		if (kikore) v.a_random_lep();
			else v.b_random_lep();
		kikore=!kikore;
		cout << endl;
	}
	return 0;
}