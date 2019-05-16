/**
*
* @file heap.hpp
* @author tekda
* Kupac adatszerkezet iterátorokkal
* Prioritásos sor csomagolóosztály, kupaccal
*
*/

#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "heap_exceptions.hpp"

template <class I>
bool validateHeap(I first, I last);

template <class T>
class Heap {
    /**
    *
    *   Konténer vektor
    *
    */
    std::vector<T> v;

    /*indexek
    */
    inline unsigned int lef(unsigned int id) {return 2*id+1;}
    inline unsigned int rig(unsigned int id) {return 2*id+2;}
    inline unsigned int par(unsigned int id) {return floor((id-1)/2);}

    /**
    *
    * Kupacban elemet feljebbmozgató eljárás
    *
    * @param index az elem indexe, amit feljebb kell mozgatni
    *
    */
    void liftUp(unsigned int index)
    {
        while (index>1 and v[par(index)]<v[index]) {
            std::swap(v[par(index)],v[index]);
        }
    }

    /**
    *
    * Kupacban elemet lejjebbmozgató eljárás
    *
    * @param index az elem indexe, amit lejjebb kell mozgatni
    *
    */
    void liftDown(unsigned int index)
    {
        while (rig(index)<v.size() and (v[index] < v[lef(index)] or v[index] < v[rig(index)]) )
        {
            if (v[rig(index)]<v[lef(index)])
                std::swap(v[index],v[lef(index)]);
            else
                std::swap(v[index],v[rig(index)]);
        }
        if (lef(index)==v.size()-1 and v[index]<v[lef(index)])
        {
            std::swap(v[index],v[lef(index)]);
        }
    }

public:
    Heap() {}
    Heap(const std::vector<T>& v_) : v(v_)
    {
        for (int i = v.size()/2 - 1; i >= 0; --i)
            liftDown(i);
    }

    /**
    *
    * Üres-e a kupac
    *
    * @return igaz, hogyha a kupac üres
    *
    */
    bool empty()
    {
        return v.size()==0;
    }

    /**
    *
    * A kupac mérete
    *
    * @return a kupac mérete.
    *
    */
    size_t size()
    {
        return v.size();
    }

    /**
    *
    * Kupacba elemet betevő eljárás
    *
    * @param item a beszúrandó elem
    *
    */
    void push(T item)
    {
        v.push_back(item);
        liftUp(v.size()-1);
    }


    /**
    *
    * Kupac maximális elemét lekérdező művelet
    *
    * @return kupac tetején lévő elem
    *
    */
    const T& top()
    {
        return v[0];
    }

    /**
    *
    * Kupacból kivesszük a legfelső elemet
    *
    */
    void pop()
    {
        std::swap(v[0],v[v.size()-1]);
        v.pop_back();
        liftDown(0);
    }

    /**
    *
    * Ellenőrző függvény
    *
    */
    void validate(bool items = false)
    {
        if (items)
        {
            for (unsigned int i=0; i<v.size(); ++i)
                std::cout << v[i] << " ";
        }
        std::cout << std::endl << "A vektor" << (validateHeap(v.begin(), v.end())?" ":" NEM ") << "teljesiti a kupac-tulajdonsagot!" << std::endl;
    }

    bool check()
    {
        return validateHeap(v.begin(), v.end());
    }

    std::vector<T> get_vector()
    {
        return v;
    }

};

template <class I>
bool validateHeap(I first, I last)
{
	if (last > first) {
		for (int i=0; i<(last-first)/2; ++i)
		{
			if ((first+2*i+1)<last && *(first+i)< *(first+2*i+1) )
				return false;
			if ((first+2*i+2)<last && *(first+i)< *(first+2*i+2) )
				return false;
		}
		return true;
	}
	else
		throw InvalidIterator();
}

#endif // HEAP_HPP
