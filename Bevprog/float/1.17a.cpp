#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "string"
#include "iomanip"

using namespace std;


int main()
{
	string s;
	cin >> s;
	if (s.at(0) == s.at(s.length()-1)) cout << "igaz"; else cout << "hamis";
	//getchar();getchar();
} 