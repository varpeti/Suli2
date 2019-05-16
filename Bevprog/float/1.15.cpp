#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"

using namespace std;


int main()
{
	char s[255];
	cin >> s;
	if (s[0]==toupper(s[0]) and not isdigit(s[0])) cout << "igaz"; else cout << "hamis";
	//getchar();getchar();
} 