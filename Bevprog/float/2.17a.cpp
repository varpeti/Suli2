#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string.h"

using namespace std;


int main()
{
	string s;
	getline(cin,s);
	string zj = "()"; int i=0; bool tart;
	while (i<s.length())
	{
		if (tart) {
			if (s.at(i)==zj.at(1)) break;
			cout << s.at(i);
		}else{
			if (s.at(i)==zj.at(0)) tart=true;
		}
		i++;
	}
	getchar();
	return 0;
} 