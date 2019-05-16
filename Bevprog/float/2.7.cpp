#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "string"
#include "iomanip"

using namespace std;


int main()
{
	int n,a,b,s;
	cin >> n;
	a=0;
	b=1;
	while(n)
	{
		s=a;
		a+=b;
		b=s;
		n--;
	}
	cout << b;
	getchar();getchar();
} 