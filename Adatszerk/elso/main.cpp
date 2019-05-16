#include "iostream"
#include "vector"

#define alma "alma";

using namespace std;

double avg(const vector<int> &v);

int main()
{
	cout << "Szia világ!" << endl;
	int i = 5;
	int &r = i;
	r++;
	cout << i << " " << r << endl;

	int *p = &i;
	int * & r2 = p;
	(*r2)++;
	cout << i << " " << *r2 << " " << r2 << " " << &r2 << endl;

	vector<int> v = {0, 1, 4};

	cout << avg(v) << endl;

	char t[5];

	cout << t[3] << endl;
	t[3]=10;
	cout << 3[t] << endl;

	const int a = 10;

	cout << a << " " << &a << endl;

	for (int i=0;i<100;i++)
	{
		cout << t[i] << " ";
	}
	//cout << alma << endl;
	getchar();
	return 0;
}

double avg(const vector<int> &v)
{
	double sum = 0.0;
	for (int i:v){sum+=i;}
	return sum/v.size();
}