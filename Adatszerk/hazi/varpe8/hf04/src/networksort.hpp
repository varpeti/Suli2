#ifndef NETWORKSORT_H_
#define NETWORKSORT_H_

#include <algorithm>
#include "exp.hpp"

template <typename T>
void rendezo_halozat(T *tomb, int meret)
{   
    if (log2(meret)!=(int)log2(meret)) throw EXP("invaild_size");
    for (unsigned int k = 1; k < (unsigned int)meret; k*=2)
        for (unsigned int i = k; i >= 1; i/=2)
        {
            bool irany = true;
            unsigned int irany_counter = 0;
            int volt_counter = 0;
            for (unsigned int j = 0; j+i < (unsigned int)meret; j++)
            {
                if (volt_counter==(int)i) volt_counter=-i; volt_counter++;
                if (volt_counter<=0) continue;
                if (irany_counter==k) {irany=!irany; irany_counter=0;} irany_counter++;
                if (irany) {if (tomb[j]>tomb[i+j]) std::swap<T>(tomb[j],tomb[i+j]);}
                else {if (tomb[j]<tomb[i+j]) std::swap<T>(tomb[j],tomb[i+j]);}
            }
        }
}

#endif