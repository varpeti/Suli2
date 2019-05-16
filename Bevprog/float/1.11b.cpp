#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"

using namespace std;


int main()
{
	float a1,a2;
	float b1,b2;
	cin >> a1 >> a2;
	cin >> b1 >> b2;
	cout << fixed << setprecision(1) << sqrt(pow(a1-b1,2) + pow(a2-b2,2));
	getchar();getchar();
} 