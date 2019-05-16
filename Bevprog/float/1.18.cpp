#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string.h"

using namespace std;

int main()
{
	string a,b;
	getline(cin,a);
	getline(cin,b);
	if (a.length()<5 or b.length()<5) {
		cout << "hamis";
		return 0;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (a.at(i)!=b.at(i)){
			cout << "hamis";
			return 0;
		}
	}
	cout << "igaz";
	return 0;
} 

a = a/i
