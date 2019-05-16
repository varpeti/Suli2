#ifndef AVL_TREE_HPP_INCLUDED
#define AVL_TREE_HPP_INCLUDED

#include <algorithm>
#include <iostream>

#include "exceptions.hpp"

using namespace std;

//
// AVL fa osztály
// DEFINÍCIÓ
//
template<class T>
class avl_tree
{
private:

    // Belsõ csúcs struktúra, kiegészítve a magassággal
    class Node
    {
    public:
        Node *parent;
        Node *left, *right;
        int height; //új meta-adat a részfa ideiglenes magasságának tárolásához
        T key;

        Node(const T& k) : parent(nullptr), left(nullptr), right(nullptr), height(1), key(k) {}
        Node(const T& k, Node *p) : parent(p), left(nullptr), right(nullptr), height(1), key(k) {}

        //-2, -1, 0, 1 és 2 lehet, megfeleltethető a diákban szereplő --, ++, stb. jelölésnek
        int balance_factor() const
        {
            return _height(right) - _height(left);
        }

        void update_height()
        {
            height = std::max(_height(left), _height(right)) + 1;
        }

    private:
        // Segédfüggvény NIL Node-ok magasságához
        static int _height(const Node *x)
        {
            return (x == nullptr) ? 0 : x->height;
        }
    };

    // Gyökér elem
    Node *root;

    // Felszabadító függvény
    void _destroy(Node *x);

    // Bináris keresőfa segédfüggvények
    Node *_min(Node *x) const;
    Node *_max(Node *x) const;
    Node *_next(Node *x) const;
    Node *_prev(Node *x) const;

    ostream& _inorder(Node* i, ostream& o);
    ostream& _preorder(Node* i, ostream& o);
    ostream& _postorder(Node* i, ostream& o);

    size_t _size(Node *x) const;

    // Új kereső segédfüggvény
    Node *_find(const T & key) const;

    // AVL kiegyensúlyozó függvények
    void _rotate_left(Node *x);
    void _rotate_right(Node *x);
    void _rebalance(Node *x);

    // Ellenõrzõ segédfüggvény
    void _validate_avl(Node *x) const;

public:
    // Konstruktor és destruktor
    avl_tree() : root(nullptr) {}
    ~avl_tree() { _destroy(root); }

    // Másoló konstruktor és értékadás operátor, valamint segéd függgvényeik
    avl_tree(const avl_tree<T>& t);
    avl_tree& operator=(const avl_tree<T>& t);
    Node *getroot() const;
    Node* copyOf( Node* n, Node* p );

    // Alapmûveletek
    size_t size() const { return _size(root); }
    bool isempty() const { return root==nullptr; }

    bool find(const T& k) const;
    void insert(const T& k);
    void remove(const T& k);

    ostream& inorder(ostream& o);
    ostream& preorder(ostream& o);
    ostream& postorder(ostream& o);

    // Ellenõrzõ függvény
    void validate() const;
};

//
// AVL fa osztály
// FÜGGVÉNYIMPLEMENTÁCIÓK
//

// Balra forgatás ...
// az x csúcs körül, illetve más szóhasználattal
// az x csúcs és a jobb gyereke közötti él mentén.
// Előfeltétel, hogy x és a jobb gyereke létezzenek.
template<class T>
void avl_tree<T>::_rotate_left(Node *x)
{
	// TODO
}

// Jobbra forgatás ...
// az x csúcs körül, illetve más szóhasználattal
// az x csúcs és a bal gyereke közötti él mentén.
// Előfeltétel, hogy x és a bal gyereke létezzenek.
template<class T>
void avl_tree<T>::_rotate_right(Node *x)
{
	// TODO
}

// Az újrakiegyensúlyozó függvény
// ** Az AVL fa lelke **
//
// Miután a módosító mûveletet (beszúrást vagy törlést) a bináris keresõfáknál
// tanult módon végrehajtottuk, ezt a függvényt kell meghívni a beszúrt, illetve
// az eltávolítottuk csúcs szülõjére, hogy a fában felfelé haladva frissítse a
// magasságinformációkat, és szükség esetén forgatásokkal helyreállítsa az AVL
// fa tulajdonságait.
//
// Pontos elõfeltételek:
// x NIL, vagy
// x mindkét részfája érvényes, kiegyensúlyozott AVL fa helyes magasságértékekkel
// (üres részfa is helyes AVL fa)
template<class T>
void avl_tree<T>::_rebalance(Node *)
{
	while (x!=nullptr)
    {   
        int old_height = x->parent->height; //régi méret mentése

        if (x->balance_factor() == 2){ //++
            Node *y = x->right;
            if (y->balance_factor() == -1){ //-
                _rotate_right(y);
                y->update_height();
            }
            // itt már (++,0) vagy (++,+)
            _rotate_left(x);
            x->update_height();
            x=x->parent; // x lejjebb kerül ezért lépünk vissza
        }else 
        if (x->balance_factor() == -2){ //--
            Node *y = x->left;
            if (y->balance_factor() == 1){ //+
                _rotate_left(y);
                y->update_height();
            }
            // itt már (--,0) vagy (--,-)
            _rotate_right(x);
            x->update_height();
            x=x->parent;
        }

        x->update_height();
        if (x->height == old_height) break; // Jó az AVL fa tulajdonság

        x = x->parent; // Feljebb lépünk
    }
}

// Rekurzívan felszabadítja a csúcsokat.
// A destruktor hívja meg a gyökérre.
template<class T>
void avl_tree<T>::_destroy(Node *x)
{
    if (x != nullptr)
    {
        _destroy(x->left);
        _destroy(x->right);
        delete x;
    }
}

// Segéd függvény a copy constructor-hoz valamint assigment operator-hoz
template<class T>
typename avl_tree<T>::Node* avl_tree<T>::copyOf( Node* n, Node* p ){

	if( n == nullptr ) return nullptr;		// Ha a másolandó node üres nincs dolgunk

	Node* x = new Node(n->key, p);			// Létrehozzuk az új node-ot a másik fa a alapján, de az új fához kapcsoljuk
	x->left = copyOf( n->left, x );
	x->right = copyOf( n->right, x );

	return x;
}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template<class T>
avl_tree<T>::avl_tree(const avl_tree<T>& t) {

	Node* n = t.getroot();					// A másolandó fa gyökér node-ja
	Node* x = new Node(n->key, n->parent);	// Az új fa első node-ja, n -ről másolva
	root = x;								// Ez lesz az új fa gyökere
	x->left = copyOf( n->left, x );			// A gyökér bal részfájának felépítése
	x->right = copyOf( n->right, x );		// A gyökér jobb részfájának felépítése
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template<class T>
avl_tree<T>& avl_tree<T>::operator=(const avl_tree<T>& t) {

	if(&t == this) return *this;			// Ha a két fa megegyezik nincs dolgunk

	_destroy(root);							// Ha nem, akkor először töröljük a már meglévő fát

	Node* n = t.getroot();
	Node* x = new Node(n->key, n->parent);
	root = x;
	x->left = copyOf( n->left, x );
	x->right = copyOf( n->right, x );

	return *this;

}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename avl_tree<T>::Node *avl_tree<T>::_min(Node *x) const
{
    while (x->left != nullptr)
        x = x->left;
    return x;
}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename avl_tree<T>::Node *avl_tree<T>::_max(Node *x) const
{
    while (x->right != nullptr)
        x = x->right;
    return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy nil-t, ha x az legnagyobb kulcsú elem.
// Előfeltétel: x != nil
template<class T>
typename avl_tree<T>::Node *avl_tree<T>::_next(Node *x) const
{
    if (x->right != nullptr)
        return _min(x->right);

    Node *y = x->parent;
    while (y!=nullptr && x==y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy nil-t, ha x az legkisebb kulcsú elem.
// Előfeltétel: x != nil
template<class T>
typename avl_tree<T>::Node *avl_tree<T>::_prev(Node *x) const
{
    if (x->left != nullptr)
        return _max(x->left);

    Node *y = x->parent;
    while (y!=nullptr && x==y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerû részfa elemeinek számát.
// Megjegyzés: üres fára is mûködik -> 0-t ad vissza
template<class T>
size_t avl_tree<T>::_size(Node *x) const
{
    if (x == nullptr)
        return 0;
    else
        return _size(x->left) + _size(x->right) + 1;
}

// Lekérdezi, hogy található-e k kulcs a fában.
template<class T>
typename avl_tree<T>::Node *avl_tree<T>::_find(const T & key) const
{
    Node *x = root;
    while (x != nullptr)
    {
        if (key < x->key)
        {
            x = x->left;
        }
        else if(x->key < key)
        {
            x = x->right;
        }
        else
        {
            return x;
        }
    }
    return nullptr;
}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template<class T>
bool avl_tree<T>::find(const T& k) const
{
    return _find(k) != nullptr;
}

// Beszúrja a k értéket a fába.
// Ha már van k érték a fában, akkor nem csinál semmit.
template<class T>
void avl_tree<T>::insert(const T& k)
{
    // Keresés
    Node *p = nullptr; //p: parent
    Node *x = root;

    while (x != nullptr)
    {
        p = x;
        if (k < x->key)
        {
            x = x->left;
        }
        else if(x->key < k)
        {
            x = x->right;
        }
        //Ha megtaláltuk a beszúrandó elemet, nincs más dolgunk.
        else
        {
            return;
        }
    }

    // Új csúcs létrehozása és bekötése
    x = new Node(k, p);
    if (p == nullptr)
        root = x;
    else if (x->key < p->key)
        p->left = x;
    else
        p->right = x;

    // Beszúrás utáni kiegyensúlyozás
    _rebalance(p);
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template<class T>
void avl_tree<T>::remove(const T& k)
{
    // Keresés
    Node *z = _find(k);

    // Ha nincs ilyen kulcsú elem a fában, úgy nincs dolgunk.
    if (z == nullptr)
    	return;

    // Csúcs kivágása a fából és felszabadítás
    //y: az a csúcs, amit törölni fogunk
    //w: 'y' szülõje
    //x: 'y' gyereke (ha van neki)
    Node *x, *y, *w;

    if (z->left == nullptr || z->right==nullptr)
        y = z;
    else
        y = _next(z);

    w = y->parent;
    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    if (x != nullptr)
        x->parent = y->parent;
    if (y->parent == nullptr )
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        z->key = y->key;
    delete y;

    // Törlés utáni kiegyensúlyozás
    _rebalance(w);
}

// Rekurzív segédfüggvény a validate() függvényhez
// Ellenõrzi, hogy az x gyökerû fára teljesülnek-e az AVL tulajdonságok.
template<class T>
void avl_tree<T>::_validate_avl(Node *x) const
{
    if (x != nullptr)
    {
        _validate_avl(x->left);
        _validate_avl(x->right);

        //Magasság ellenõrzése
        int h = x->height;
        x->update_height();
        if (x->height != h)
        {
            throw invalid_avl_tree();
        }

        //AVL tulajdonság ellenõrzése
        if (std::abs(x->balance_factor()) > 1)
        {
            throw invalid_avl_tree();
        }
    }
}

// Ez a függvény a debuggolást segíti.
// Ellenõrzi, hogy a gyökérbõl elérhetõ fa érvényes
// bináris keresõfa, illetve érvényes AVL fa-e.
template<class T>
void avl_tree<T>::validate() const
{
    // Keresõfa tulajdonság ellenõrzése bejárással
    if (root != nullptr)
    {
        Node *x = _min(root);
        T prev = x->key;
        x = _next(x);
        while (x)
        {
            if (!(prev < x->key))
            {
                throw invalid_binary_search_tree();
            }
            prev = x->key;
            x = _next(x);
        }
    }

    // AVL fa tulajdonság ellenõrzése
    _validate_avl(root);
}

// Bináris keresőfa bejárások kívülről elérhető függvényei.
template<class T>
ostream& avl_tree<T>::preorder(ostream& o)
{
    if(isempty()){
    	cout << "A fa ures!" <<endl;
        return o;
    }
    return _preorder(root, o);
}

template<class T>
ostream& avl_tree<T>::postorder(ostream& o)
{
    if(isempty()){
    	cout << "A fa ures!" <<endl;
        return o;
    }
    return _postorder(root, o);
}

template<class T>
ostream& avl_tree<T>::inorder(ostream& o)
{
    if(isempty()){
    	cout << "A fa ures!" <<endl;
        return o;
    }
    return _inorder(root, o);
}

// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template<class T>
ostream& avl_tree<T>::_preorder(Node *i, ostream& o)
{
    o << i->key << ", ";
    if(i->left!=nullptr)
        _preorder(i->left, o);
    if(i->right!=nullptr)
        _preorder(i->right, o);
    return o;
}

// Postorder bejárás.
template<class T>
ostream& avl_tree<T>::_postorder(Node* i, ostream& o)
{
    if(i->left!=nullptr)
        _postorder(i->left, o);
    if(i->right!=nullptr)
        _postorder(i->right, o);
    o << i->key << ", ";
    return o;
}

// Inorder bejárás.
template<class T>
ostream& avl_tree<T>::_inorder(Node* i, ostream& o)
{
    if(i->left!=nullptr)
        _inorder(i->left,o);
    o << i->key << ", ";
    if(i->right!=nullptr)
        _inorder(i->right,o);
    return o;
}

template<class T>
typename avl_tree<T>::Node *avl_tree<T>::getroot() const
{
    if(isempty())
        throw internal_error("A fa ures.");
    return root;
}

#endif // AVL_TREE_HPP_INCLUDED
