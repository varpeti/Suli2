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

	int i = 1;
	while(i*i<n)
	{
		cout << i*i << " ";
		i++;
	}
	getchar();getchar();
} 