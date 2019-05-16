/**
*
* @file main.cpp
* @author tekda
* @author horar
* Főprogram, kupac és prioritásos sor demonstrálására
*
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
//#include "pqueue.hpp"
#include "heap_sort.hpp"

#define ARRAY_SIZE 30

int main ()
{
	srand(time(0));
	try
	{
        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Kezdeti vektor";
        std::cout << std::endl << "-----------------------------" << std::endl;

        std::vector<int> v;

        for(int i=0; i < ARRAY_SIZE; ++i)
        {
            v.push_back(rand()%100);
            std::cout << v[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Kupacca alakitva";
        std::cout << std::endl << "-----------------------------" << std::endl; std::cout << std::endl;

        Heap<int> h_1;
        for (unsigned int i=0;i<v.size();++i)
            h_1.push(v[i]);
        h_1.validate(true);

        std::cout << std::endl;
        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Kupacba illesztunk egypar szamot";
        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Ezeket: ";
        int val;
        for (int i=0;i<5;++i) {
            val = rand()%100;
            std::cout << val << " ";
            h_1.push(val);
        }
        std::cout << std::endl;
        h_1.validate(true);
        std::cout << std::endl;

        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Kiveszunk egypar szamot a kupac tetejerol";
        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Ezeket: ";
        for (int i=0; i<5; ++i)
        {
            std::cout << h_1.top() << " ";
            h_1.pop();
        }
        std::cout << std::endl;
        h_1.validate(true);


        std::cout << std::endl << "-----------------------------" << std::endl;
        std::cout << "Kupac rendezes";
        std::cout << std::endl << "-----------------------------" << std::endl;

        std::vector<int> t;

        for (int i=0; i<ARRAY_SIZE; ++i)
        {
            int val = rand()%100;
            t.push_back(val);
            std::cout << val << ' ';
        }

        heapSort(t);
        std::cout << std::endl << "rendezve: " << std::endl;

        for(int i=0; i<ARRAY_SIZE; ++i)
        {
            std::cout << t[i] << ' ';
        }

//        std::cout << std::endl << "-----------------------------" << std::endl;
//        std::cout << "Prioritasos sor";
//        std::cout << std::endl << "-----------------------------" << std::endl;
//
//        PriorityQueue<int> pq;
//        std::cout << std::endl;
//        std::cout << "Beillesztunk elemeket: ";
//
//        for (int i=0;i<ARRAY_SIZE;++i)
//        {
//            val = rand()%100;
//            std::cout << val << " ";
//            pq.push(val, val); // itt most teszteljük, hogy a priority és a value ugyanaz
//            //pq.push(val, rand()%100/20.0);
//        }
//        std::cout << std::endl << (pq.validate()?"Rendben van!":"Valami nem oke!") << std::endl;
//        std::cout << std::endl;std::cout << std::endl;
//        std::cout << "Kiveszunk egypar elemet: ";
//        for (int i=0;i<5;++i) {
//            std::cout << pq.top() << " ";
//            pq.pop();
//        }
//        std::cout << std::endl << (pq.validate()?"Rendben van!":"Valami nem oke!") << std::endl;
//        std::cout << std::endl;std::cout << std::endl;
//        std::cout << "A sorban maradt elemek: ";
//        while (!pq.empty()) {
//            std::cout << pq.top() << " ";
//            pq.pop();
//        }
//        std::cout << std::endl << (pq.validate()?"Rendben van!":"Valami nem oke!") << std::endl;

        std::cout << std::endl << "----------------------------------------------------------" << std::endl;
        std::cout << "Veget ert a program futasa, ha minden rendben van, akkor minden rendben van!";
        std::cout << std::endl << "----------------------------------------------------------" << std::endl;

    }
    catch (HeapException e)
    {
            std::cout << "HIBA!!";
	}

	return 0;

}
