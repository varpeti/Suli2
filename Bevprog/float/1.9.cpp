#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"

using namespace std;


int main()
{
	float a1,a2,a3;
	cin >> a1 >> a2 >> a3;
	float s = (a1+a2+a3)/2;
	cout << fixed << setprecision(1) << sqrt(s*(s-a1)*(s-a2)*(s-a3));
	getchar();getchar();
} 