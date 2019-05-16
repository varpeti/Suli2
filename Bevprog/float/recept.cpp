#include "iostream"
#include "fstream"
#include "sstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string.h"

using namespace std;

struct adat
{
	string anyag;
	double mennyiseg;
};

void be_n(ifstream& be,std::vector<adat>& v)
{	
	adat seged;
	char kuka;
	
	while (be >> seged.mennyiseg >> kuka >> ws && getline(be,seged.anyag))
	{
		v.push_back(seged);
	}
}

int main()
{
	std::vector<adat> v;

	ifstream be ("recept.txt");
		be_n(be,v);
	be.close();

	adat max; max = v[0];
	adat min; min = v[0];
	int db = 0;

	string mit;
	getline(cin,mit);

	for (adat i : v)
	{
		//cout << i.mennyiseg << i.anyag << endl;
		if (max.mennyiseg<i.mennyiseg) max = i;
		if (min.mennyiseg>i.mennyiseg) min = i;
		if (i.mennyiseg<1) db++;
		if (i.anyag.compare(mit)==0) cout << "Kell: " << i.mennyiseg << endl;
	}
	cout << max.mennyiseg << max.anyag << endl
	 	<< min.mennyiseg << min.anyag << endl
		<< db << endl;
	getchar();
	return 0;
} 