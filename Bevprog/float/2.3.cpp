#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "string"
#include "iomanip"

using namespace std;


int main()
{
	int a,b;
	cin >> a >> b;

	int i = 0;
	while(a>=i and b>=i)
	{
		i++;
		if (a%i==0 and b%i==0) cout << i << " ";
	}
	//getchar();getchar();
} 