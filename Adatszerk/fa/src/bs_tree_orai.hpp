#ifndef BIN_TREE_HPP_INCLUDED
#define BIN_TREE_HPP_INCLUDED

#include <algorithm>
#include <iostream>

#include "exceptions.hpp"

using namespace std;

//
// Bináris keresőfa osztály
// DEFINÍCIÓ
//
template<class T>
class Bs_tree {
	// Belső csúcs struktúra
	class Node {
	public:
		Node* parent;
		Node* left, *right;
		T key;

		Node(const T& k) :
				parent(nullptr), left(nullptr), right(nullptr), key(k) {
		}
		Node(const T& k, Node* p) :
				parent(p), left(nullptr), right(nullptr), key(k) {
		}
	};

	// Adattag
	Node* root;

	// Felszabadító függvény
	void _destroy(Node* x);

	// Segédfüggvények
	Node* _min(Node* x) const;
	Node* _max(Node* x) const;
	Node* _next(Node* x) const;
	Node* _prev(Node* x) const;

	ostream& _inorder(Node* i, ostream& o);
	ostream& _preorder(Node* i, ostream& o);
	ostream& _postorder(Node* i, ostream& o);

	size_t _size(Node* x) const;

public:
	// Konstruktor és destruktor
	Bs_tree() :
			root(nullptr) {
	}
	~Bs_tree() {
		_destroy(root);
	}

	// Másoló konstruktor és operátor, valamint segéd függvényeik
	Bs_tree(const Bs_tree<T>& t);
	Bs_tree& operator=(const Bs_tree<T>& t);
	Node* getroot() const;
	Node* copyOf(Node* n, Node* p);

	// Alapműveletek
	size_t size() const {
		return _size(root);
	}
	bool isempty() const {
		return root == nullptr;
	}

	bool find(const T& k) const;
	void insert(const T& k);
	void remove(const T& k);

	ostream& inorder(ostream& o);
	ostream& preorder(ostream& o);
	ostream& postorder(ostream& o);

};

//
// Bináris keresőfa osztály
// FÜGGVÉNYIMPLEMENTÁCIÓK
//

// Rekurzívan felszabadítja a csúcsokat.
// A destruktor hívja meg a gyökérre.
template<class T>
void Bs_tree<T>::_destroy(Node* x) {
	if (x != nullptr) {
		_destroy(x->left);
		_destroy(x->right);
		delete x;
	}
}

// Segéd függvény a copy constructor-hoz valamint assigment operator-hoz
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::copyOf(Node* n, Node* p) {

	if (n == nullptr)
		return nullptr;		// Ha a másolandó node üres nincs dolgunk

	Node* x = new Node(n->key, p);// Létrehozzuk az új node-ot a másik fa a alapján, de az új fához kapcsoljuk
	x->left = copyOf(n->left, x);
	x->right = copyOf(n->right, x);

	return x;
}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template<class T>
Bs_tree<T>::Bs_tree(const Bs_tree<T>& t) {

	Node* n = t.getroot();					// A másolandó fa gyökér node-ja
	Node* x = new Node(n->key, n->parent);// Az új fa első node-ja, n -ről másolva
	root = x;								// Ez lesz az új fa gyökere
	x->left = copyOf(n->left, x);		// A gyökér bal részfájának felépítése
	x->right = copyOf(n->right, x);		// A gyökér jobb részfájának felépítése
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template<class T>
Bs_tree<T>& Bs_tree<T>::operator=(const Bs_tree<T>& t) {

	if (&t == this)
		return *this;			// Ha a két fa megegyezik nincs dolgunk

	_destroy(root);			// Ha nem, akkor először töröljük a már meglévő fát

	Node* n = t.getroot();
	Node* x = new Node(n->key, n->parent);
	root = x;
	x->left = copyOf(n->left, x);
	x->right = copyOf(n->right, x);

	return *this;

}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::_min(Node* x) const {
	while (x->left != nullptr)
		x = x->left;
	return x;
}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::_max(Node* x) const {
	while (x->right != nullptr)
		x = x->right;
	return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy nil-t, ha x az legnagyobb kulcsú elem.
// Előfeltétel: x != nilif(isempty())
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::_next(Node* x) const {
	if (x->right != nullptr)
		return _min(x->right);

	Node *y = x->parent;
	while (y != nullptr && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy nil-t, ha x az legkisebb kulcsú elem.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::_prev(Node* x) const {
	if (x->left != nullptr)
		return _max(x->left);

	Node *y = x->parent;
	while (y != nullptr && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerű részfa elemeinek számát.
// Megjegyzés: üres fára is működik -> 0-t ad vissza
template<class T>
size_t Bs_tree<T>::_size(Node* x) const {
	if (x == nullptr)
		return 0;
	else
		return _size(x->left) + _size(x->right) + 1;
}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template<class T>
bool Bs_tree<T>::find(const T& k) const {
	Node *x = root;
	while (x != nullptr && (k < x->key || x->key < k)) {
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;				// Ez egyenértékű a "return x!=nullptr;" -rel
}

// Beszúrja a k értéket a fába.
// Ha már van k érték a fában, akkor nem csinál semmit.
template<class T>
void Bs_tree<T>::insert(const T& k) {
	// Keresés
	Node *y = nullptr;
	Node *x = root;

	// == operátor mellőzése céljából az egyenlőségvizsgálatot a < operátor segítségével valósítjuk meg
	while (x != nullptr && (k < x->key || x->key < k)) // x!=0 && !(k==x->key)
	{
		y = x;
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}

	// Ha van már ilyen kulcsú elem a fában, úgy nincs dolgunk.
	if (x != nullptr)
		return;

	// Új csúcs létrehozása és bekötése
	x = new Node(k, y);
	if (y == nullptr)
		root = x;
	else if (x->key < y->key)
		y->left = x;
	else
		y->right = x;
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template<class T>
void Bs_tree<T>::remove(const T& k) {
	// Keresés
	Node* z = root;
	while (z != nullptr && (k < z->key || z->key < k))
		if (k < z->key)
			z = z->left;
		else
			z = z->right;

	// Ha nincs ilyen kulcsú elem a fában, úgy nincs dolgunk.
	if (z == nullptr)
		return;

	// Csúcs kivágása a fából és felszabadítás
	Node* y;
	if (z->left == nullptr || z->right == nullptr)
		y = z;
	else
		y = _next(z);

	Node* x;
	if (y->left != nullptr)
		x = y->left;
	else
		x = y->right;

	if (x != nullptr)
		x->parent = y->parent;
	if (y->parent == nullptr)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if (y != z)
		z->key = y->key;
	delete y;
}

// Bináris keresőfa bejárások kívülről elérhető függvényei.
template<class T>
ostream& Bs_tree<T>::preorder(ostream& o) {
	if (isempty()) {
		cout << "A fa ures!" << endl;
		return o;
	}
	return _preorder(root, o);
}

template<class T>
ostream& Bs_tree<T>::postorder(ostream& o) {
	if (isempty()) {
		cout << "A fa ures!" << endl;
		return o;
	}
	return _postorder(root, o);
}

template<class T>
ostream& Bs_tree<T>::inorder(ostream& o) {
	if (isempty()) {
		cout << "A fa ures!" << endl;
		return o;
	}
	return _inorder(root, o);
}

// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template<class T>
ostream& Bs_tree<T>::_preorder(Node* i, ostream& o) {
	o << i->key << ", ";
	if (i->left != nullptr) {
		_preorder(i->left, o);
	}
	if (i->right != nullptr) {
		_preorder(i->right, o);
	}
	return o;
}

// Postorder bejárás.
template<class T>
ostream& Bs_tree<T>::_postorder(Node* i, ostream& o) {
	if (i->left != nullptr) {
		_postorder(i->left, o);
	}
	if (i->right != nullptr) {
		_postorder(i->right, o);
	}
	o << i->key << ", ";
	return o;
}

// Inorder bejárás.
template<class T>
ostream& Bs_tree<T>::_inorder(Node* i, ostream& o) {
	if (i->left != nullptr) {
		_inorder(i->left, o);
	}
	o << i->key << ", ";
	if (i->right != nullptr) {
		_inorder(i->right, o);
	}
	return o;
}

template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::getroot() const {
	if (isempty())
		throw internal_error("A fa ures.");
	return root;
}

#endif // BIN_TREE_HPP_INCLUDED
