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
		//      Futtatunk egy tesztet, amely 1000 véletlen számot szúr be az AVL fánkba.
		//      Minden egyes beszúrás után ellenõrizzük, hogy az adatszerkezet érvényes AVL fa-e.
		//
		//      Hogy kizárjuk annak lehetõségét, hogy véletlenül csúcsokat drótozunk ki a fából,
		//      amikor nem is akarunk törölni, ugyanezeket a számokat beszúrjuk egy std::set-be is,
		//      majd ellenõrizzük, hogy a két adatszerkezet ugyanannyi elemet tartalmaz.
		//
		//      Végül az std::set-bõl az elemeket kimásoljuk egy std::vector-ba, amit megkeverünk,
		//      hogy véletlenszerû sorrendben tudjuk törölni az összes elemet a fából.
		//      Ezzel ellenõrizzük, hogy a törlés jól mûködik-e, és a végén megnézzük, hogy tényleg
		//      üres lett-e az AVL fánk.

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

        //Üres fa tesztelése
        avl_tree<int> uresFa;
        cout << "\n*** Probaljunk kiolvasni egy ures fat: ***\n";
        uresFa.inorder( cout );

		//      Most egymillió véletlen számot szúrunk be az AVL fába, és párhuzamosan egy
		//      std::set-be. Csak a végén ellenõrizzük, hogy érvényes-e az AVL fa és egyezik-e
		//      a két adatszerkezet mérete.
		//
		//      Ezután megnézzük, hogy minden std::set-beli elem megtalálható-e az AVL fában,
		//      majd sorban kitöröljuk õket, és ellenõrizzük, hogy üres lett-e a fa.
		//
		//      Ennek a tesztnek néhány másodperc alatt le kell futnia. Ha fél percnél tovább
		//      tart, akkor olyan hiba lehet a kódban, ami elrontja az aszimptotikus futási idõt.

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
