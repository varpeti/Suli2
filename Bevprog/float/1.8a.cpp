#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string"

using namespace std;


int main()
{
	float a1,a2;
	cin >> a1 >> a2;
	cout << fixed << setprecision(1) << (a2-a1+a2);
	getchar();getchar();

	return 0;
} 