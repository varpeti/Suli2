#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"

using namespace std;


int main()
{
	float a1,a2,a3;
	float b1,b2,b3;
	cin >> a1 >> a2 >> a3;
	cin >> b1 >> b2 >> b3;
	cout << fixed << setprecision(1) << a2*b3-a3*b2 << endl << a3*b1-a1*b3 << endl << a1*b2-a2*b1;
	getchar();getchar();
} 