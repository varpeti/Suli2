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
	cout << s.at(0) << ". ";
	int i=0;
	while (i<s.length())
	{
		//cout << s.at(i) << " ";
		//printf("%i\n",s.at(i));
		if (s.at(i)==32) {cout << s.at(i+1) << "."; break;}
		i++;
	}
	getchar();
	return 0;
} 