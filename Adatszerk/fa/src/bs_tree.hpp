#ifndef BIN_TREE_HPP_INCLUDED
#define BIN_TREE_HPP_INCLUDED

#include <algorithm>
#include <iostream>
#include <stack> // bejárásokhoz kell.

#include "exceptions.hpp"

using namespace std;

//
// Bináris keresőfa osztály
// DEFINÍCIÓ
//
template<class K, class V>
class Bs_tree {
    // Belső csúcs struktúra
    struct Node {
        Node *Pparent;
        Node *Pleft, *Pright;
        K key;
        V value;


        Node(const K& k, const V& v) :
                Pparent(nullptr), Pleft(nullptr), Pright(nullptr), key(k), value(v) {
            //cout << "Létrejöttem: " << key << " = " << value << " | " << this << endl;
        }
        Node(const K& k, const V& v, Node *p) :
                Pparent(p), Pleft(nullptr), Pright(nullptr), key(k), value(v) {
            //cout << "Létrejöttem: " << key << " = " << value << " | " << this << endl;
        }
        ~Node(){
            //cout << "Megszüntem: " << key << " = " << value << " | " << this << endl;
        }
    };

    // Adattag
    Node *root;
    size_t meret;

    // Felszabadító függvény
    void _destroy(Node *x);

    // Segédfüggvények
    Node *_min(Node *x) const;
    Node *_max(Node *x) const;
    Node *_next(Node *x) const;
    Node *_prev(Node *x) const;

    ostream& _inorder(Node* i, ostream& o);
    ostream& _preorder(Node* i, ostream& o);
    ostream& _postorder(Node* i, ostream& o);

    size_t _size(Node *x) const;

public:
    // Konstruktor és destruktor
    Bs_tree() {
        root = nullptr;
        meret = 1;
    }
    ~Bs_tree() {
        if (root!=nullptr) _destroy(root);
    }

    // Másoló konstruktor és operátor, valamint segéd függvényeik
    Bs_tree(const Bs_tree<K,V>& t);
    Bs_tree& operator=(const Bs_tree<K,V>& t);
    Node* getroot() const;
    Node* copyOf(Node* n, Node* p);

    // Alapműveletek
    size_t size() const {
        //return _size(root);
        return meret;
    }
    bool isempty() const {
        return root == nullptr;
    }

    bool find(const K& k) const;
    V    get(const K& k);
    void insert(const K& k,const V& v);
    void remove(const K& k);

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
template<class K, class V>
void Bs_tree<K,V>::_destroy(Node *x) {
    if (x->Pleft!=nullptr) _destroy(x->Pleft);
    if (x->Pright!=nullptr) _destroy(x->Pright);

    // A szülőjének a megfelelő gyermekét nullptre állítjuk
    if (x->Pparent!=nullptr) if (x->Pparent->Pleft==x) x->Pparent->Pleft=nullptr; else x->Pparent->Pright=nullptr;
    delete x;
}

// Segéd függvény a copy constructor-hoz valamint assigment operator-hoz
template<class K, class V>
typename Bs_tree<K,V>::Node* Bs_tree<K,V>::copyOf(Node* n, Node* p) {
    // TODO
}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template<class K, class V>
Bs_tree<K,V>::Bs_tree(const Bs_tree<K,V>& t) {
    root = nullptr;
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template<class K, class V>
Bs_tree<K,V>& Bs_tree<K,V>::operator=(const Bs_tree<K,V>& t) {
    // TODO
}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template<class K, class V>
typename Bs_tree<K,V>::Node *Bs_tree<K,V>::_min(Node *x) const {
    while (x->Pleft) x=x->Pleft;
    return x;
}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != nil
template<class K, class V>
typename Bs_tree<K,V>::Node *Bs_tree<K,V>::_max(Node *x) const {
    while (x->Pright) x=x->Pright;
    return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy nil-t, ha x az legnagyobb kulcsú elem.
// Előfeltétel: x != nilif(isempty())
template<class K, class V>
typename Bs_tree<K,V>::Node *Bs_tree<K,V>::_next(Node *x) const {
    x = x->Pright;
    x = _min(x);
    return x;
}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy nil-t, ha x az legkisebb kulcsú elem.
// Előfeltétel: x != nil
template<class K, class V>
typename Bs_tree<K,V>::Node *Bs_tree<K,V>::_prev(Node *x) const {
    x = x->Pleft;
    x = _max(x);
    return x;
}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerű részfa elemeinek számát.
// Megjegyzés: üres fára is működik -> 0-t ad vissza
template<class K, class V>
size_t Bs_tree<K,V>::_size(Node *x) const {
    // TODO
}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template<class K, class V>
bool Bs_tree<K,V>::find(const K& k) const {
    if (root==nullptr) return V();
    Node *x = root;
    while (true)
    {   
        if (x->key < k) // Ha nagyobb jobbra
        {
            if (x->Pright!=nullptr) x = x->Pright;  else return false;
        }else
        if (k < x->key) // Ha kisebb balra
        {
            if (x->Pleft!=nullptr) x = x->Pleft;    else return false;
        }else return true;
    }
}

// Megkeresi a fában a k kulcshoz tartozó értéket.
// Üres ha nem létezik.
template<class K, class V>
V Bs_tree<K,V>::get(const K& k) {
    if (root==nullptr) return V();
    Node *x = root;
    while (true)
    {   
        if (x->key < k) // Ha nagyobb jobbra
        {
            if (x->Pright!=nullptr) x = x->Pright;  else return V();
        }else
        if (k < x->key) // Ha kisebb balra
        {
            if (x->Pleft!=nullptr) x = x->Pleft;    else return V();
        }else return x->value; // Egyenlő, visszatér vele.
    }
}

// Beszúrja a k kulcsú v adatot a fába.
// Ha már van k kulcs a fában, akkor módosítja.
template<class K, class V>
void Bs_tree<K,V>::insert(const K& k,const V& v) {
    if (root==nullptr) {root= new Node(k,v); return;}
    Node *x = root;
    while (true)
    {   
        if (x->key < k) // Ha nagyobb jobbra
        {
            if (x->Pright!=nullptr) x = x->Pright;  else break;
        }else
        if (k < x->key) // Ha kisebb balra
        {
            if (x->Pleft!=nullptr) x = x->Pleft;    else break;
        }else
        //if ( !(x->key < k) and !(k < x->key) ) // Egyenlő
        {
            x->value = v;
            return;
        }
    }
    //Létrehozás, bekötés
    Node *uj = new Node(k,v,x);
    if (k < x->key) x->Pleft = uj;
    else x->Pright = uj;
    meret++;
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template<class K, class V>
void Bs_tree<K,V>::remove(const K& k) {
    if (root==nullptr) return;
    Node *x = root;
    while (true)
    {   
        if (x->key < k) // Ha nagyobb jobbra
        {
            if (x->Pright!=nullptr) x = x->Pright;  else return;
        }else
        if (k < x->key) // Ha kisebb balra
        {
            if (x->Pleft!=nullptr) x = x->Pleft;    else return;
        }else break; // Ha egyenlő
    }
    meret--;
    while (true)
    {
        switch ( (x->Pleft!=nullptr)+(x->Pright!=nullptr) ) // Mennyi gyereke van.
        {
            case 0: // Nincs gyermeke
                // A szülőjének a megfelelő gyermekét nullptre állítjuk
                if (x->Pparent!=nullptr) {if (x->Pparent->Pleft==x) x->Pparent->Pleft=nullptr; else x->Pparent->Pright=nullptr;} else root=nullptr; 
                delete x;
                return;
            case 1: // Egy gyermeke van.
                // Átadja a maga helyére a gyermekét.                                              // bal vagy jobb gyermek                                                                                   // A rotot töröltük
                if (x->Pparent!=nullptr) {if (x->Pparent->Pleft==x) x->Pparent->Pleft= (x->Pleft!=nullptr ? x->Pleft : x->Pright); else x->Pparent->Pright= (x->Pleft!=nullptr ? x->Pleft : x->Pright);} else root=(x->Pleft!=nullptr ? x->Pleft : x->Pright);
                delete x;
                return;
            case 2: // Két gyermeke van.
                Node *n = _next(x); // Megkeressük a legközelebbi rákövetkezőjét, aminek nincs bal gyermeke.
                x->key = n->key;
                x->value = n->value;
                x = n; // Majd töröljük
                break;
        }
    }
    
}

// Bináris keresőfa bejárások kívülről elérhető függvényei.
template<class K, class V>
ostream& Bs_tree<K,V>::preorder(ostream& o) {
    if (root==nullptr) return o<<"asd";
    return _preorder(root,o);
}

template<class K, class V>
ostream& Bs_tree<K,V>::postorder(ostream& o) {
    // TODO
}

template<class K, class V>
ostream& Bs_tree<K,V>::inorder(ostream& o) {
    // TODO
}

// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template<class K, class V>
ostream& Bs_tree<K,V>::_preorder(Node *i, ostream& o) {
    
    //Egy stackbe mentjük az elemeket, hogy lehessen iteratívan bejárni a fát.
    std::stack<Node *> nodeStack;
    nodeStack.push(i);
 
    while (nodeStack.empty() == false)
    {
        // Kiveszük a legfelsőt
        Node *x = nodeStack.top();
        o << "key: " << x->key << " value: " << x->value << endl;
        nodeStack.pop();
 
        // Berakjuk a gyermekeit (ha vannak)
        if (x->Pright!=nullptr)
            nodeStack.push(x->Pright);
        if (x->Pleft!=nullptr)
            nodeStack.push(x->Pleft);
    }
    return o;
}

// Postorder bejárás.
template<class K, class V>
ostream& Bs_tree<K,V>::_postorder(Node* i, ostream& o) {
    // TODO
}

// Inorder bejárás.
template<class K, class V>
ostream& Bs_tree<K,V>::_inorder(Node* i, ostream& o) {
    // TODO
}

template<class K, class V>
typename Bs_tree<K,V>::Node* Bs_tree<K,V>::getroot() const {
    return root;
}

#endif // BIN_TREE_HPP_INCLUDED
