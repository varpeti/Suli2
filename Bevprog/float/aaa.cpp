#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

#define ellenoriz(felt, pont) if (felt) pont++; else cerr << "Nem teljesul a feltetel a " << __LINE__<< ". sorban." <<endl;

/* Szabalyok:
    - csak az a beugró érvényes, amely nem tartalmaz semmilyen változtatást a main()-ben,
        és már nincs benne kommentezve semmi
    - az "ellenoriz"-en kívül nem tartalmaz #define sorokat, és azt sem szabad megváltoztatni
*/

// Innentol

char* memory = "A";

int fv(float a)
{
	return int(a/2);
}

struct Tomb
{
	std::vector<int> v;
	int osszeg = 0;
	/*Tomb()
	{
		osszeg=0;
	};
	Tomb(int s,int e)
	{
		for (int i = 0; i < s; i++)
		{
			v.push_back(e);
		}
	}*/
};

void legyen_egyenlo(Tomb& k,Tomb t)
{
	for (int e : t.v)
	{
		k.v.push_back(e);
	} 
}

bool egyenlo_e(Tomb k, Tomb t)
{
	if (k.v.size()!=t.v.size()) return false;
	int i = 0;
	for (int e : k.v)
	{
		if (e!=t.v[i]) return false;
		i++;
	}
	return true;
}

void osszead(Tomb& j)
{
	for (int e : j.v)
	{
		j.osszeg+=e;
	}
}


// Idaig

int main()
{
    int pont = 64;

    for (int i = 0; i < 100; ++i)
    {
    	if (memory[i]==64) {
    		//cout << memory[i-1] << memory[i] << memory[i+1] << endl;
    		printf("%i%i%i\n",memory[i-1],memory[i],memory[i+1]);
    		//memory[i]=94;
    	}
    }

    int a = fv(4);
    int b = fv(2);
    ellenoriz(a == 2 && b == 1 , pont)

    Tomb t;
    ellenoriz(t.v.size()==0 , pont)

    t.v = vector<int>(8,2);
    ellenoriz(t.v.size()==8 , pont)

    Tomb k;
    legyen_egyenlo(k,t);
    ellenoriz(k.v.size()==8 , pont)

    bool b1 = egyenlo_e(k,t);
    k.v[3]=3;
    bool b2 = egyenlo_e(k,t);
    ellenoriz(b1==true && b2==false , pont)
    osszead(t);
    osszead(k);
    ellenoriz( t.osszeg == 16 && k.osszeg == 17 , pont)
    cout << endl << pont << "/6 pont";
}
