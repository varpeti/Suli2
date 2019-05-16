#include "avl_tree.hpp"

#include <ctime>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	try
	{
		//      Futtatunk egy tesztet, amely 1000 v�letlen sz�mot sz�r be az AVL f�nkba.
		//      Minden egyes besz�r�s ut�n ellen�rizz�k, hogy az adatszerkezet �rv�nyes AVL fa-e.
		//
		//      Hogy kiz�rjuk annak lehet�s�g�t, hogy v�letlen�l cs�csokat dr�tozunk ki a f�b�l,
		//      amikor nem is akarunk t�r�lni, ugyanezeket a sz�mokat besz�rjuk egy std::set-be is,
		//      majd ellen�rizz�k, hogy a k�t adatszerkezet ugyanannyi elemet tartalmaz.
		//
		//      V�g�l az std::set-b�l az elemeket kim�soljuk egy std::vector-ba, amit megkever�nk,
		//      hogy v�letlenszer� sorrendben tudjuk t�r�lni az �sszes elemet a f�b�l.
		//      Ezzel ellen�rizz�k, hogy a t�rl�s j�l m�k�dik-e, �s a v�g�n megn�zz�k, hogy t�nyleg
		//      �res lett-e az AVL f�nk.

		cout << "\n*** Kis elemszamu, reszletes teszt futtatasa ***\n" << endl;

		set<int> stdShort;
		avl_tree<int> myShort;
		for (int i = 0; i < 1000; i++)
		{
			if (i % 100 == 0)
				cout << i + 100 << " elem beszurasa...";

			int x = rand();
			stdShort.insert(x);
			myShort.insert(x);
			myShort.validate();

			if ((i + 1) % 100 == 0)
				cout << " ok." << endl;
		}

		if (myShort.size() != stdShort.size())
			throw internal_error("Meret nem egyezik!");
		cout << "\nMeret rendben.\n" << endl;

		// Copy construktor teszt
		avl_tree<int> myShort2( myShort );
		cout << "\nPreorder kiolvasas : ";	myShort.preorder(cout);
		cout << "\nPreorder kiolvasas 2: ";	myShort2.preorder(cout);
		cout << endl << endl;

		vector<int> arrayShort(stdShort.begin(), stdShort.end());
		random_shuffle(arrayShort.begin(), arrayShort.end());

		for (unsigned i = 0; i < arrayShort.size(); i++)
		{
			if (i % 100 == 0)
				cout << i + 100 << " elem torlese...";

			myShort.remove(arrayShort[i]);
			myShort.validate();

			if ((i + 1) % 100 == 0 || i + 1 == arrayShort.size())
				cout << " ok." << endl;
		}
		if (myShort.size() != 0)
			throw internal_error("Meret nem egyezik!");
		cout << "\nMeret rendben.\n" << endl;

        //�res fa tesztel�se
        avl_tree<int> uresFa;
        cout << "\n*** Probaljunk kiolvasni egy ures fat: ***\n";
        uresFa.inorder( cout );

		//      Most egymilli� v�letlen sz�mot sz�runk be az AVL f�ba, �s p�rhuzamosan egy
		//      std::set-be. Csak a v�g�n ellen�rizz�k, hogy �rv�nyes-e az AVL fa �s egyezik-e
		//      a k�t adatszerkezet m�rete.
		//
		//      Ezut�n megn�zz�k, hogy minden std::set-beli elem megtal�lhat�-e az AVL f�ban,
		//      majd sorban kit�r�ljuk �ket, �s ellen�rizz�k, hogy �res lett-e a fa.
		//
		//      Ennek a tesztnek n�h�ny m�sodperc alatt le kell futnia. Ha f�l percn�l tov�bb
		//      tart, akkor olyan hiba lehet a k�dban, ami elrontja az aszimptotikus fut�si id�t.

		cout << "\n*** Nagy elemszamu teszt futtatasa ***\n" << endl;

		cout << "Beszuras...";
		set<int> stdLong;
		avl_tree<int> myLong;
		for (int i = 0; i < 1000000; i++)
		{
			int x = rand();
			stdLong.insert(x);
			myLong.insert(x);
		}

		myLong.validate();
		if (myLong.size() != stdLong.size())
			throw internal_error("Meret nem egyezik!");
		cout << " ok." << endl;

		cout << "Torles...";
		for (set<int>::iterator it = stdLong.begin(); it != stdLong.end(); it++)
		if (!myLong.find(*it))
			throw internal_error("Elem veszett el a fabol!");

		for (set<int>::iterator it = stdLong.begin(); it != stdLong.end(); it++)
			myLong.remove(*it);

		myLong.validate();
		if (myLong.size() != 0)
			throw internal_error("Meret nem egyezik!");
		cout << " ok." << endl;

	}
	catch (const exception& e)
	{
		cout << "HIBA: " << e.what() << endl;
	}

	getchar();
	return 0;
}
