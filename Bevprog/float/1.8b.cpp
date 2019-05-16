#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"

using namespace std;


int main()
{
	float a1,a2,n;
	cin >> a1 >> a2 >> n;
	cout << fixed << setprecision(1) << (a1+(n-1)*(a2-a1));
	getchar();getchar();
} 