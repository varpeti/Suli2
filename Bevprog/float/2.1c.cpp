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
	if (n>1) cout << endl;
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j <=i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	getchar();getchar(); 
} 