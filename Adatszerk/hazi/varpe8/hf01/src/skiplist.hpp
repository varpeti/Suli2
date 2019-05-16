/*/
	+	A munkámat a "A Skip List Cookbook - William Pugh - 1990" alapján készítettem.
	+	Templeate kiegészítés: bármi lehet key aminek a "<" definiálva van.
/*/


#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <iostream>
#include <stdlib.h>

#define MAXSZINT 10

//DEF//

template<typename TK, typename TV>
class SKIPLIST
{
	private:
		struct NODE
		{
			NODE(TK _key, TV _value);
			~NODE();

			TK key;
			TV value;
			NODE *Pnext[MAXSZINT];
		};

		NODE *header;
		size_t meret;

		int randomLevel();

	protected:
	public:
		SKIPLIST();
		~SKIPLIST();
		void insert(TK key,TV value);
		void erase(TK key);
		bool contains(TK key);
		TV get(TK key);
		size_t size();

};

//HEAD
template<typename TK, typename TV>
SKIPLIST<TK,TV>::NODE::NODE(TK _key, TV _value)
{
	//std::cout << "Letrejottem: " << _key << " " << _value << " " << this << "\n";
	value = _value;
	key = _key;
	for (int i = 0; i < MAXSZINT; ++i)
	{
		Pnext[i]=nullptr;
	}
}

template<typename TK, typename TV>
SKIPLIST<TK,TV>::NODE::~NODE()
{
	//std::cout << "Megszuntem: " << key << " " << value << " " << this << "\n";
}

template<typename TK, typename TV>
SKIPLIST<TK,TV>::SKIPLIST()
{
	header = new NODE(TK(),TV());
	meret = 0;
}

template<typename TK, typename TV>
SKIPLIST<TK,TV>::~SKIPLIST()
{
	
	NODE *x = header;

	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr)
		{
			erase(x->Pnext[i]->key); //Kitörlöm a legkisebbtől kezdve az egészet.
		}
	}
	delete header; //Majd a headert is.
}

//PRIV//
template<typename TK, typename TV>
int SKIPLIST<TK,TV>::randomLevel() // Ezt késöbb át lehet írni optimálisabbra mint a véletlen.
{
	int lvl = 1; // lvl1 től indul mivel a 0. szintnek mindenképp létre kell jönnie.
	while (rand() %2 == 0 and lvl<MAXSZINT)
	{
		lvl++;
	}
	return lvl;
}


//PROT//

//PUB//
template<typename TK, typename TV>
void SKIPLIST<TK,TV>::insert(TK key, TV value)
{
	NODE *update[MAXSZINT];
	NODE *x = header;

	for (int i = MAXSZINT-1; i >= 0; --i) // Megkeresi az szigoróan kissebb értékűt (x), és a keresztül mutatókat (update).
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->key < key)
		{
			x = x->Pnext[i];
		}
		update[i]=x;
	}
	x = x->Pnext[0];
	if (x==nullptr or x->key != key) // Ha nem létezik,
	{
		int newLevel = randomLevel();
		x = new NODE(key,value);
		for (int i = 0; i < newLevel; ++i) // Létrehozom a szintjeivel együtt,
		{
			x->Pnext[i]=update[i]->Pnext[i]; // amire mutatott az elötte lévő arra fog mutatni,
			update[i]->Pnext[i]=x; // és az elötte lévő rámutat.
		}
		meret++;
	}else	// Ha létezik
	{
		x->value=value; //Módosítja az értékét
	}
}

template<typename TK, typename TV>
void SKIPLIST<TK,TV>::erase(TK key)
{
	NODE *update[MAXSZINT];
	NODE *x = header;

	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->key < key)
		{
			x = x->Pnext[i];
		}
		update[i]=x;
	}
	x = x->Pnext[0];
	if (x!=nullptr and x->key == key) // Ha létezik és megegyezik az értéke
	{
		for (int i = 0; i < MAXSZINT; ++i) //Minden szinten
		{
			if (update[i]->Pnext[i]!=x) break; // Ha van
			update[i]->Pnext[i]=x->Pnext[i]; // A rámutató az adott szinten mutasson arra amire mutatott eddig.
		}
		delete x; //Törlés
		meret--;
	}

}

template<typename TK, typename TV>
bool SKIPLIST<TK,TV>::contains(TK key)
{
	NODE *x = header;
	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->key < key)
		{
			x = x->Pnext[i];
		}
	}
	x=x->Pnext[0];
	if (x!=nullptr and x->key==key) return true;
	return false;
}

template<typename TK, typename TV>
TV SKIPLIST<TK,TV>::get(TK key)
{
	NODE *x = header;
	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->key < key)
		{
			x = x->Pnext[i];
		}
	}
	x=x->Pnext[0];
	if (x!=nullptr and x->key==key) return x->value;
	return TV();
}

template<typename TK, typename TV>
size_t SKIPLIST<TK,TV>::size()
{
	return meret; //Gyorsabb mint bejárni.
}

#endif