#include <iostream>
#include <string>

using namespace std; 

bool van_benne_p0(string str)
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {      
        if ( str.at(i)=='\0' ) return true;
    }
    return false;
}

void print(string str,string nev)
{
	
}

void osszehas(string a, string b, string an, string bn)
{
	cout << "\t\t" << an << "\t" << bn << endl;
	cout << "\ttartalma: " << a << "\t" << b << endl;
	cout << "\tvan \\0  : " << van_benne_p0(a) << "\t" << van_benne_p0(b) << endl;
	cout << "\tmerete  : " << a.size() << "\t" << b.size() << endl;
	cout << "\t" << an << "==" << bn << ": " << (a==b) << endl << endl;
}


int main()
{	
	string a1="q",a2="qq";

	// Jó módszer
	string alma1 = ""; 
	alma1 += a1 + '\0';
	alma1 += a2 + '\0';
	
	string alma2 = "";
	alma2 += a2 + '\0';
	alma2 += a1 + '\0';

	//Rossz
	string banan1 = "q\0qq\0";
	string banan2 = "qq\0q\0";

	// Jó
	string szilva1 = "q"; 
	szilva1.push_back('\0');
	szilva1 += "qq";
	szilva1.push_back('\0');

	string szilva2 = "qq";
	szilva2.push_back('\0');
	szilva2 += "q";
	szilva2.push_back('\0');

	//Rossz
	string kivi1 = ""; 
	kivi1 += "q" + '\0'; //azért mert a "q" az igazából char[] és nem string
	kivi1 += "qq" + '\0';

	string kivi2 = "";
	kivi2 += "q" + '\0';
	kivi2 += "qq" + '\0';

	//Rossz
	string korte1 = "";
	korte1 += a1 + "\0";
	korte1 += a2 + "\0";

	string korte2 = "";
	korte2 += a2 + "\0";
	korte2 += a1 + "\0";

	//Adatok kiírása
	osszehas(alma1,alma2,"alma1","alma2");
	osszehas(banan1,banan2,"banan1","banan2");
	osszehas(szilva1,szilva2,"szilva1","szilva2");
	osszehas(kivi1,kivi2,"kivi1","kivi2");
	osszehas(korte1,korte2,"korte1","korte2");

	return 0;
}

/*Kimenet:
			alma1	alma2
	tartalma: qqq	qqq
	van \0  : 1		1
	merete  : 5		5
	alma1==alma2: 0

			banan1	banan2
	tartalma: q		qq
	van \0  : 0		0
	merete  : 1		2
	banan1==banan2: 0

			szilva1	szilva2
	tartalma: qqq	qqq
	van \0  : 1		1
	merete  : 5		5
	szilva1==szilva2: 0

			kivi1	kivi2
	tartalma: qqq	qqq
	van \0  : 0		0
	merete  : 3		3
	kivi1==kivi2: 1

			korte1	korte2
	tartalma: qqq	qqq
	van \0  : 0		0
	merete  : 3		3
	korte1==korte2: 1

*/
