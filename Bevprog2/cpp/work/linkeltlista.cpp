#include "iostream"
#include "sstream"
#include "math.h"
#include "time.h"


using namespace std;

struct A
{
	int x;
	A *next;
	A(int xx){x=xx;}
	void insert(int xx); // utánna rakja
	void insert(int xx,A *&kezdo); // elé rakja
	void remove(A *&kezdo);
};

void A::insert(int xx)
{
	A *a = new A(xx);
	a->next=next;
	next=a;
}

void A::insert(int xx, A *&kezdo)
{
	A *a = new A(xx);

	if (kezdo==this)
	{
		a->next=kezdo;
		kezdo = a;
		return;
	}

	A *i = kezdo;
	while (i)
	{	
		if (i->next==this) {
			a->next=this;
			i->next=a;
			return;
		}
		i = i->next;
	}
}

void A::remove(A *&kezdo)
{
	if (kezdo==this)
	{
		kezdo=next;
		delete this;
		return;
	}

	A *i = kezdo;
	while (i)
	{	
		if (i->next==this) {
			i->next=next;
			delete this;
			return;
		}
		i = i->next;
	}
}


int main()
{	
	A *kezdo = new A(11); //11
	kezdo->next = NULL;

	kezdo->insert(12); //11 12
	kezdo->insert(13); //11 13 12
	kezdo->next->insert(14); // 11 13 14 12
	kezdo->remove(kezdo); // 13 14 12
	kezdo->insert(15); // 13 15 14 12
	kezdo->next->next->remove(kezdo); // 13 15 12
	kezdo->insert(16,kezdo); // 16 13 15 12
	kezdo->next->insert(17,kezdo); // 16 17 13 15 12

	A *i = kezdo;
	while (i)
	{	
		cout << i->x << " ";
		i = i->next;
	}
	
	return 0;
} 