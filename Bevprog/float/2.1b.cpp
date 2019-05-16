#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "string"
#include "iomanip"

using namespace std;


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int i = 0; i < n; ++i)
		{
			cout << "*";
		}
		cout << endl;
	}
	getchar();getchar(); 
} 