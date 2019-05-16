#include <ctime>
#include <iostream>
#include "bs_tree.hpp"

using namespace std;

void run()
{
    Bs_tree<int,int> tree,ures;

    /*/
                10
               /  \
              04   11
             /  \    \
           03    07   12
          /     /  \
        02    05    08
                \
                 06

    /*/

    tree.insert(10,10);
    tree.insert(4,4);
    tree.insert(11,11);
    tree.insert(3,3);
    tree.insert(7,7);
    tree.insert(12,12);
    tree.insert(2,2);
    tree.insert(5,5);
    tree.insert(6,6);
    tree.insert(8,8);
    
    tree.preorder(cout); cout << "Size: "<< tree.size() << endl;
    tree.remove(4);
    tree.preorder(cout); cout << "Size: "<< tree.size() << endl;
    tree.remove(10);
    tree.preorder(cout); cout << "Size: "<< tree.size() << endl;

    for (int i = -10; i < 25; ++i)
    {
        if (tree.find(i)) cout << tree.get(i) << endl; 
    }
}

int main()
{
    run();
    getchar();
    return 0;
}
/*/
int main() {
    srand(time(0));

    try {
        cout << "\n*** Binaris keresofa teszt futtatas: ***\n" << endl;

        int myArray[10] = { 44, 61, 68, 67, 40, 20, 74, 17, 36, 60 };

        Bs_tree<int,int> myShort;
        for (int i = 0; i < 10; i++) {
            cout << i << " elem beszurasa...";

            int x = myArray[i]; //rand();
            myShort.insert(x,x);

            cout << " Sikerult " << myArray[i] << "-t beszurni." << endl;

        }

        if (myShort.size() != 10) {
            cout << myShort.size() << endl;
            throw internal_error("Meret nem megfelelo!");
        }
        cout << "\nMeret rendben.\n" << endl;

        //olvassuk ki inorder módon egy tömbbe
        cout << "\nInorder kiolvasas: ";
        myShort.inorder(cout);

        cout << "\nPreorder kiolvasas: ";
        myShort.preorder(cout);

        cout << "\nPostorder kiolvasas: ";
        myShort.postorder(cout);
        cout << endl;

        // másoljuk le a fát és irassuk ki ezt is
        Bs_tree<int,int> myShort2(myShort);
        cout << "\nInorder kiolvasas 2: ";
        myShort2.inorder(cout);

        cout << "\nPreorder kiolvasas 2: ";
        myShort2.preorder(cout);

        cout << "\nPostorder kiolvasas 2: ";
        myShort2.postorder(cout);
        cout << endl;

        cout << "\nTorles tesztelese:\n";

        myShort.remove(20);
        myShort.remove(44);
        myShort.remove(17);
        myShort.remove(40);
        myShort.remove(60);

        //Mi van most a gyökérben?
        cout << "A gyoker == " << myShort.getroot()->key << endl;

        //Üres fa tesztelése
        Bs_tree<int,int> uresFa;
        cout << "\n Probaljunk kiolvasni egy ures fat: \n";
        //uresFa.inorder(cout);
    } catch (const exception& e) {
        cout << "HIBA: " << e.what() << endl;
    }

    getchar();
    return 0;
}//*/
